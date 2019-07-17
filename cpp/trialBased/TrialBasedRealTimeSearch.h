#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <limits>
#include <math.h>
#include "../utility/ResultContainer.h"
#include "../utility/DiscreteDistribution.h"
using namespace std;

template <class Domain>
class THTS_RT{
    typedef typename Domain::State State;
    typedef typename Domain::Cost Cost;
    typedef typename Domain::HashState Hash;

public:
    struct Node {
        State state; // State
        unordered_set<Node*> successors; // Children
        double fval; // Name this value something
        double g; 
        // From the paper, path costs from root node to a node is g(n). It is not stored, but calculated on demand...
        // But looking at their pseudo code, it seems that it is stored
        int visits; // Number of visits
        bool lock; // Lock

		Node* parent;
        bool initialized;
        
        // Extended values beyond the paper
        double h;
        double d;
        double derr;
        double epsH;
        double epsD;
        double expectedMinimumPathCost;

    public:
        Node(State state, double val, int visit, bool lock, Node* parent) : state(state), fval(val), visits(visit), lock(lock), parent(parent){
            initialized = false;
            g = 0;
        }

        double getGValue() const { return g; }
		double getHValue() const { return h; }
		double getDValue() const { return d; }
        double getFValue() const { return g + h; }
        double getFHatValue() const { return g + getHHatValue(); }
        double getDHatValue() const { return (derr / (1.0 - epsD)); }
        double getHHatValue() const { return h + getDHatValue() * epsH; }
    };

    // Max queue
    struct max_g {
        bool operator()(const Node* n1, const Node* n2){
            if (n1->g  == n2->g){
                n1->getHValue() > n2->getHValue();
            }
            return n1->g < n2->g;
        }
    };

    struct min_f {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->getFValue() == n2->getFValue()){
                n1->getGValue() > n2->getGValue();
			}
			return n1->getFValue() > n2->getFValue();
        }
    };

    struct max_f {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->getFValue() == n2->getFValue()){
                n1->getGValue() > n2->getGValue();
			}
			return n1->getFValue() < n2->getFValue();
        }
    };

    struct min_fhat {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->getFHatValue() == n2->getFHatValue()){
                n1->getGValue() > n2->getGValue();
			}
			return n1->getFHatValue() > n2->getFHatValue();
        }
    };

    struct max_fhat {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->getFHatValue() == n2->getFHatValue()){
                n1->getGValue() > n2->getGValue();
			}
			return n1->getFHatValue() < n2->getFHatValue();
        }
    };

    struct min_h {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->getHValue() == n2->getHValue()){
				// return rand() % 2;
                n1->getGValue() > n2->getGValue();
			}
			return n1->getHValue() > n2->getHValue();
        }
    };

    struct min_fval {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->fval == n2->fval){
				// return rand() % 2;
                n1->getGValue() > n2->getGValue();
			}
			return n1->fval > n2->fval;
        }
    };

    // In the paper, they use max pqueue on g, which make sense if g is uniform.
    // In hard domains, max g may 
    typedef priority_queue<Node*, vector<Node*>, max_g> PQueue; // Max queue
    
    THTS_RT(Domain& domain, string algorithm, int lookahead, string decision = "") 
                    : domain(domain), algorithm(algorithm), lookahead(lookahead), decision(decision){
        srand(1);
        if (algorithm == "AS"){
            trial_expansion = "bfs";
            trial_backup = "bfs";
        } else if (algorithm == "WAS"){
            trial_expansion = "bfs";
            trial_backup = "bfs";
            w = 5;
        } else if (algorithm == "UCT"){
            trial_expansion = "uct";
            trial_backup = "uct";
        } else if (algorithm == "GUCT"){
            trial_expansion = "uct";
            trial_backup = "uct";
            k = 0;
        } else if (algorithm == "UCTS"){
            trial_expansion = "uct";
            trial_backup = "bfs";
        } else if (algorithm == "GUCTS"){
            trial_expansion = "uct";
            trial_backup = "bfs";
            k = 0;
        } else if (algorithm == "GUCTN"){
            trial_expansion = "uct";
            trial_backup = "nancy";
            k = 0;
        } else if (algorithm == "GUCTB"){
            trial_expansion = "uct";
            trial_backup = "bellman";
            k = 0; 
        } else {
            cout << "Invalid algorithm: " << algorithm << endl;
            exit(1);
        }  
    }
    
    // Extending what values the 
    void updateNode(Node* n, double h, double d, double derr, double epsH, double epsD){
        n->d = d;
        n->h = h;
        n->derr = derr;
        n->epsH = epsH;
        n->epsD = epsD;
    }

    void resetNode(Node* n){
        root->parent = NULL;
        root->successors.clear();
        root->initialized = false;
    }

    double pathCost(Node* n){
        double g = 0;
        Node* cur = n;
        while (cur->parent){
            g +=  domain.getEdgeCost(cur->state);
            cur = cur->parent;
        }
        return g;
    }

    ResultContainer getPlan(){
        ResultContainer res;
        State root_state = domain.getStartState();

        domain.initialize(algorithm, lookahead);

        root = new Node(root_state, w * domain.heuristic(root_state), 1, false, NULL);
        updateNode(root, domain.heuristic(root_state), domain.distance(root_state), 
                            domain.distanceErr(root_state), domain.epsilonHGlobal(), domain.epsilonDGlobal());

        while(true){
            if (domain.isGoal(root->state)){
                res.solutionCost = root->g;
                res.solutionFound = true;
                break;
            }

            int exp = res.nodesExpanded;
            unordered_map<State, Node*, Hash> TT;
            TT[root->state] = root;
            domain.updateEpsilons();

            // Expansion phase
            while (res.nodesExpanded - exp < lookahead){
                performTrial(TT, res);
                if (goal_found){
                    goal_found = false;
                    break;
                }
            }
            
            // Learning phase
            dijkstra(TT);

            // Action selection phase
            root = selectAction(root, TT);

            updateParent(root->parent);
            resetNode(root);
                       
            // Add this step to the path taken so far
            if (record_plan){
                res.path.push(root->state.getLabel());
            }

            // Clean up tree
            for (auto it : TT){
                if (it.second != root){
                    delete(it.second);
                }
            }
        }

        delete(root);

        if (res.nodesGenerated > trial_limit){
            cout << "Node generation limit reached." << endl;
            res.solutionFound = false;
        }

        return res;
    }

    void updateParent(Node* n){
        // RTA* style, update state to the second best heuristic + edgecost
        // Change current state h to the sencond best, RTA* style
        priority_queue<double, vector<double>, greater<double>> minheap;
        for (Node* child : n->successors){
            minheap.push(n->g + domain.getEdgeCost(child->state) + domain.heuristic(child->state));
        } 
        if (minheap.size() > 1){
            minheap.pop();
        }
        domain.updateHeuristic(n->state, minheap.top());
    }


    void dijkstra(unordered_map<State, Node*, Hash> TT){
        // Learning using reverse Dijkstra
        priority_queue<Node*, vector<Node*>, min_h> open;
        // vector<Node*>open;

        // unordered_set<Node*> open_set;
        // Start by initializing every state in closed to inf h
        for (auto it : TT){
            // Nodes that are initialized are equivalent to them being in the closed list
            if (it.second->initialized){
                // domain.updateHeuristic(it.first, numeric_limits<double>::infinity());
            } else {
                // open.push_back(it.second);
                open.push(it.second);
                // open_set.insert(it.second);
            }
        }

        while(!open.empty()){
            Node* cur = open.top();
            open.pop();
            if (cur->parent){
                State s = cur->parent->state;
                if (domain.heuristic(s) > domain.getEdgeCost(cur->state) + domain.heuristic(cur->state)){
                    // Update the heuristic of this pedecessor
                    domain.updateHeuristic(s, domain.getEdgeCost(cur->state) + domain.heuristic(cur->state));
                    // Update the distance of this predecessor
                    domain.updateDistance(s, domain.distance(cur->state) + 1);
                    // Update the distance for the heuristic error of this predecessor
                    domain.updateDistanceErr(s, domain.distanceErr(cur->state));
                    cur->parent->d = domain.distance(s);
                    cur->parent->derr = domain.distanceErr(s);
                    cur->parent->h = domain.heuristic(s);
                    open.push(cur->parent);
                }
            }
        }

        // for (Node* n : open){
        //     if (!(n->parent)){
        //         continue;
        //     }

        //     Node* cur = n;
        //     State s = cur->parent->state;
        //     while (domain.heuristic(s) > domain.getEdgeCost(cur->state) + domain.heuristic(cur->state)){
                // // Update the heuristic of this pedecessor
                // domain.updateHeuristic(s, domain.getEdgeCost(cur->state) + domain.heuristic(cur->state));
                // // Update the distance of this predecessor
                // domain.updateDistance(s, domain.distance(cur->state) + 1);
                // // Update the distance for the heuristic error of this predecessor
                // domain.updateDistanceErr(s, domain.distanceErr(cur->state));
                // cur->parent->d = domain.distance(s);
                // cur->parent->derr = domain.distanceErr(s);
                // cur->parent->h = domain.heuristic(s);
                // cur = n;
                // s = cur->parent->state;
        //     }
        // }
       
       /*
        while (!TT.empty() && !open.empty()){
            Node* cur = open.top();
			open.pop();
            open_set.erase(cur);
            TT.erase(cur->state);

            for (State s : domain.predecessors(cur->state)){
                if (TT.find(s) != TT.end() && 
                                domain.heuristic(s) > domain.getEdgeCost(cur->state) + domain.heuristic(cur->state)){

					// Update the heuristic of this pedecessor
					domain.updateHeuristic(s, domain.getEdgeCost(cur->state) + domain.heuristic(cur->state));
					// Update the distance of this predecessor
					domain.updateDistance(s, domain.distance(cur->state) + 1);
					// Update the distance for the heuristic error of this predecessor
					domain.updateDistanceErr(s, domain.distanceErr(cur->state));

                    TT[s]->d = domain.distance(s);
                    TT[s]->derr = domain.distanceErr(s);
                    TT[s]->h = domain.heuristic(s);

                    if (open_set.find(TT[s]) == open_set.end()){
					    open.push(TT[s]);
                        open_set.insert(TT[s]);
                    } else {
                        vector<Node*> tmp;
                        // This is not the ideal way to update a node inside a pqueue
                        // Doing this because we are using STD lib,
                        while(!open.empty()){
                            if (open.top() != TT[s]){
                                tmp.push_back(open.top());
                            }
                            open.pop();
                        }
                        // No push back node with updated heurisitic
                        open.push(TT[s]);
                        for (Node* n : tmp){
                             open.push(n);
                        }
                    }
                }
            }
        }
        */
    }

    void performTrial(unordered_map<State, Node*, Hash>& TT, ResultContainer& res){
        PQueue backUpQueue;
        Node* n = root;
        while (n->initialized){           
            State old = n->state;
            n = selectAction(n, TT);
            if (old == n->state){
                cout << "Deadend..." << endl;
                exit(1);
            }
            // cout << "At:\n" << n->state << "\n" << endl;
        }

        // If n is goal
        if (domain.isGoal(n->state)){
            goal_found = true;
            res.solutionFound = true;
            return; // Extract plan and return
        }

        initalizeNode(n, backUpQueue, TT, res);
        backUpQueue.push(n);

        // while backUpQueue is not empty do
        while (!backUpQueue.empty()){
            n = backUpQueue.top(); // m <-backUpQueue.pop()
            backUpQueue.pop();
            backUp(n, TT);

            if (n != root){
                backUpQueue.push(n->parent);
                if(TT.find(n->state) == TT.end()){
                    delete(n);
                }
            }
        }
    }

    void initalizeNode(Node* n, PQueue& backUpQueue, unordered_map<State, Node*, Hash>& TT, ResultContainer& res){
        // cout << "Initalize:\n" << n->state << "\n" << endl;
        res.nodesExpanded++;

        vector <State> children = domain.successors(n->state);
        // For each action... In this case for each children

        res.nodesGenerated += children.size();

        State bestChild;
		double bestF = numeric_limits<double>::infinity();

        for (State child : children){
            // child = s'
            auto it = TT.find(child);

            // If s' not in TT and not is not deadend then
            // TODO check deadend
            if (it == TT.end()){
                // Node(State state, int N, Cost f, int v, Node* parent)
                // n' <- <s', 0, w*h(s'), l, isGoal(s')>
                // Node* childNode(new Node(child, w * domain.heuristic(child), 1, domain.isGoal(child), n)); // n'


                // Don't lock the child if it's goal even when the paper says to. Otherwise, goal cannot be reached.
                Node* childNode = new Node(child, w * domain.heuristic(child), 1, false, n); // n'
                
                // childNode->g = pathCost(childNode);    // TODO this was not supposed to be stored in the node
                childNode->g = n->g + domain.getEdgeCost(child);
                updateNode(childNode, domain.heuristic(child), domain.distance(child), domain.distanceErr(child), 
                                domain.epsilonHGlobal(), domain.epsilonDGlobal());

                if (trial_backup == "nancy"){
                     DiscreteDistribution d = DiscreteDistribution(100, childNode->getFValue(), childNode->getFHatValue(),
						    childNode->getDValue(), childNode->getFHatValue() - childNode->getFValue());
                    childNode->fval = d.expectedCost();
                } else if (trial_backup == "bellman"){
                    childNode->fval = childNode->getFHatValue();
                }

                //TT[s'] <- n'
                TT[child] = childNode;
                // cout << child << endl;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.insert(childNode);

            } else {
                // State already in the tree, check to see if it's a better path
                int path = n->g + domain.getEdgeCost(child);
                if (path < (TT[child])->g) {

                    Node* s = (TT[child]);

                    // cout << " Better path:" << endl;
                    // cout << child << endl;
                    // cout << " Old parent:" << endl;
                    // cout << s->parent->state << endl;

                    backUpQueue.push(s->parent);
                    // N(par(TT[s'])) <- N(par(TT[s'])) \ {n'}
                    s->parent->successors.erase(s);
                    s->parent = n;
                    s->g = path;
                    s->state = child; // update label
                    n->successors.insert(s);

                    // cout << " New parent:" << endl;
                    // cout << n->state << endl;
                }
            }

            if (!TT[child]->initialized){
                if (TT[child]->getFValue() < bestF){
                    bestF = TT[child]->getFValue();
                    bestChild = child;
                }
            }
        }
        
         // Learn one-step error
        if (bestF != numeric_limits<double>::infinity()){
            double epsD = (1 + domain.distance(bestChild)) - n->getDValue();
            double epsH = (domain.getEdgeCost(bestChild) + domain.heuristic(bestChild)) - n->getHValue();
            domain.pushEpsilonHGlobal(epsH);
            domain.pushEpsilonDGlobal(epsD);
        }

        n->initialized = true;
    }

    Node* selectBFS(Node* n){
        // THTS-BFS
        // return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
        // i.e. return successor that is not locked with the lowest value
        priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<pair<double, Node*>> > pqueue; 
        for (Node* child : n->successors){
            if (prune_type == "lock" && child->lock){
                continue;
            }
            double child_value = child->fval + k * domain.getEdgeCost(child->state);
            pqueue.push(make_pair(child_value, child));
        }
        vector<Node*> ties;
        double best = pqueue.top().first;
        while(!pqueue.empty() && pqueue.top().first == best){
            ties.push_back(pqueue.top().second);
            pqueue.pop();
        }

        return ties[rand() % ties.size()];
    }

    Node* selectUCT(Node* n){
         // UTC
        priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<pair<double, Node*>> > pqueue; 
        double min = numeric_limits<double>::infinity();
        double max = 0;
        vector <double> children_fbar;

        // Finiding the max and min to use for normalization
        for (Node* child : n->successors){
            if (prune_type == "lock" && child->lock){
                continue;
            }
            double child_value = child->fval + k * domain.getEdgeCost(child->state);

            if (child_value < min){
                min = child_value;
            }
            if (child_value > max){
                max = child_value;
            }
            children_fbar.push_back(child_value);
        }

        int i  = 0;
        double denom = max - min;
        for (Node* child : n->successors){
            if (prune_type == "lock" && child->lock){
                continue;
            }
            double child_value;
            double fb = 0;
            double csq = (C * sqrt(log(n->visits)/child->visits));

            if (denom != 0){
                fb = (children_fbar[i] - min)/denom;
            }

            child_value = fb - csq;

            // cout << "  fval: " << child->fval;
            // cout << "  max:" << max;
            // cout << "  min:" << min;
            // cout << "  n:" << children_fbar[i] - min;
            // cout << "  d:" << denom;
            // cout << "  fb: " << fb;
            // cout << "  csq: " << csq;
            // cout << "  val: " << child_value << endl; 
            // cout << child->state << endl;

            pqueue.push(make_pair(child_value, child));
            ++i;
        }
    

        vector<Node*> ties;
        double best = pqueue.top().first;
        while(!pqueue.empty() && pqueue.top().first == best){
            ties.push_back(pqueue.top().second);
            pqueue.pop();
        }

        return ties[rand() % ties.size()];
    }

    Node* selectNancy(Node* n, unordered_map<State, Node*, Hash>& TT){
        Node* cur; 
        if (trial_expansion == "nancy"){
            // Node need to redundantly recalulate distribution
        priority_queue<Node*, vector<Node*>, min_fval> open;
            for (auto it : TT){
                // Nodes that are initialized are equivalent to them being in the closed list
                if (!it.second->initialized){
                    open.push(it.second);
                }
            }
            cur = open.top();
        } else {
            priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<pair<double, Node*>> > open;
            for (auto it : TT){
                // Nodes that are initialized are equivalent to them being in the closed list
                if (!it.second->initialized){
                    DiscreteDistribution d = DiscreteDistribution(100, it.second->getFValue(), it.second->getFHatValue(),
						    it.second->getDValue(), it.second->getFHatValue() - it.second->getFValue());
                    double cost = d.expectedCost();
                    open.push(make_pair(cost, it.second));
                }
            }
            cur = open.top().second;
        }

        while (cur->parent != n){
            cur = cur->parent;
        }
        return cur;
    }

    Node* selectFHat(Node* n, unordered_map<State, Node*, Hash>& TT){
        priority_queue<Node*, vector<Node*>, min_f> open;
        for (auto it : TT){
            // Nodes that are initialized are equivalent to them being in the closed list
            if (!it.second->initialized){
                open.push(it.second);
            }
        }
        Node* cur = open.top();
        while (cur->parent != n){
            cur = cur->parent;
        }
        return cur;
    }

    Node* selectF(Node* n, unordered_map<State, Node*, Hash>& TT){
        priority_queue<Node*, vector<Node*>, min_f> open;
        for (auto it : TT){
            // Nodes that are initialized are equivalent to them being in the closed list
            if (!it.second->initialized){
                open.push(it.second);
            }
        }
        Node* cur = open.top();
        while (cur->parent != n){
            cur = cur->parent;
        }
        return cur;
    }
    
    Node* selectAction(Node* n, unordered_map<State, Node*, Hash>& TT){
        // cout << "Select action:" << endl;
        // If there's only one child   
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return n;
        }

        // Min queue to be used for tie breaking
        if (decision == ""){
            // Default
            if (trial_expansion == "bfs"){
                return selectBFS(n);
            } else if (trial_expansion == "uct"){
                return selectUCT(n);
            } else {
                cout << "Invalid algorithm: " << algorithm << endl;
                exit(1);
            }  
        } else if (decision == "nancy"){
            return selectNancy(n, TT);
        } else if (decision == "fhat"){
            return selectFHat(n, TT);
        } else if (decision == "f"){
            return selectF(n, TT);
        } else {
            cout << "Invalid decision algorithm: " << decision << endl;
            exit(1);
        }  
    }

    void backUp(Node* n, unordered_map<State, Node*, Hash>& TT){
        // cout << "Back up:\n" << n->state << endl;

        if (n->successors.size() == 0){
            if (prune_type == "erase"){
                n->parent->successors.erase(n);
                // cout << "  Deadend!" << endl;
                // cout << "  Parent's succ size: " << n->parent->successors.size() << endl;
                // cout << n->parent->state << endl;
                TT.erase(n->state);
            } else if (prune_type == "lock"){
                n->lock = true;
            }
            return;
        }

        int visits = 0;
        bool lock = true;

        if (trial_backup == "bfs" ){
            // THTS-BFS
            double best_value = numeric_limits<double>::infinity();
            for (Node* child : n->successors){
                // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
                double child_value = child->fval + k * domain.getEdgeCost(child->state);
                if (child_value < best_value){
                    best_value = child_value;
                }
                visits += child->visits; // v(n) <- sum of n' in N(n) {v(n')}
                lock = lock && child->lock; // l(n) <- bools of n' in N(n) {l(n')}
            }
            n->fval = best_value;
        } else if (trial_backup == "uct"){
            double fval = 0;
            for (Node* child : n->successors){
                fval += child->visits * (child->fval + k * domain.getEdgeCost(child->state));
                visits += child->visits;
                lock = lock && child->lock;
            }
            n->fval = fval/visits;

            // cout << "  new fval: " << n->fval << endl;
        } else if (trial_backup == "nancy"){
            double best_value = numeric_limits<double>::infinity();
            for (Node* child : n->successors){
                // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
                // DiscreteDistribution d = DiscreteDistribution(100, child->getFValue(), child->getFHatValue(),
				// 		    child->getDValue(), child->getFHatValue() - child->getFValue());
                // double child_value = d.expectedCost();
                double child_value = child->fval;
                if (child_value < best_value){
                    best_value = child_value;
                }
                visits += child->visits; // v(n) <- sum of n' in N(n) {v(n')}
                lock = lock && child->lock; // l(n) <- bools of n' in N(n) {l(n')}
            }
            n->fval = best_value;

        } else if (trial_backup == "bellman"){
            double best_value = numeric_limits<double>::infinity();
            for (Node* child : n->successors){
                // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
                double child_value = child->getFHatValue();
                if (child_value < best_value){
                    best_value = child_value;
                }
                visits += child->visits; // v(n) <- sum of n' in N(n) {v(n')}
                lock = lock && child->lock; // l(n) <- bools of n' in N(n) {l(n')}
            }
            n->fval = best_value;
        } else {
            cout << "Invalid backup algorithm: " << trial_backup << endl;
            exit(1);
        }

        n->visits = visits;
        n->lock = lock;
    }

    void setK(double v){
        k = v;
    }

    void setW(double v){
        w = v;
    }

    void setC(double v){
        C = v;
    }

    void setPruning(string type){
        prune_type = type;
    }

    void setRecordPlan(bool b){
        record_plan = b;
    }

protected:
    Domain& domain;
    double w = 1;
    double k = 1;
    int lookahead;
    int trial_limit = 10000000;
    double C = 1.4; // exploration parameter C
    bool goal_found = false;
    Node* root;
    string decision;
    string algorithm;
    string trial_expansion;
    string trial_backup;
    string prune_type = "erase"; // default to removing deadends
    bool record_plan = false;
};