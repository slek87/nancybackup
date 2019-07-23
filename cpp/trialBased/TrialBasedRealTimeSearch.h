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
        double value; // Means the heuristic for greedy algorithms, f for non greedy
        int visits; // Number of visits
        bool lock; // Lock

		Node* parent;
        bool initialized;
        double edgeCost;
        
        // Extended values beyond the paper
        double h;
        double d;
        double derr;
        double epsH;
        double epsD;

    public:
        Node(State state, double val, int visit, bool lock, Node* parent, double h, double d, double derr, double epsH, double epsD)
                        : state(state), value(val), visits(visit), lock(lock), parent(parent), h(h), d(d), derr(derr), epsH(epsH), epsD(epsD){
            initialized = false;
            edgeCost = 0;
        }

        double getGValue() const { 
            const Node *cur = this;
            double gCost = 0;
            while(cur->parent){
                gCost += edgeCost;
                cur = cur->parent;
            }
            return gCost; 
        }
        double getFValue() const { return getGValue() + h; }
        double getFHatValue() const { return getGValue() + getHHatValue(); }
        double getDHatValue() const { return (derr / (1.0 - epsD)); }
        double getHHatValue() const { return h + getDHatValue() * epsH; }
    };

    struct maxG {
        bool operator()(const Node* n1, const Node* n2){
            if (n1->getGValue()  == n2->getGValue()){
                return rand() % 2;
            }
            return n1->getGValue() < n2->getGValue();
        }
    };

    struct minH {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->h == n2->h){
                n1->getGValue() < n2->getGValue();
			}
			return n1->h > n2->h;
        }
    };

    struct minF {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->getFValue() == n2->getFValue()){
                return rand() % 2;
			}
			return n1->h > n2->h;
        }
    };

    // In the paper, they use max pqueue on g, which make sense if g is uniform.
    typedef priority_queue<Node*, vector<Node*>, maxG> PQueue; // Max queue
    
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
        } else if (algorithm == "UCTN"){
            trial_expansion = "uct";
            trial_backup = "bfs";
            backup_type = "nancy";
        } else if (algorithm == "GUCTN"){
            trial_expansion = "uct";
            trial_backup = "bfs";
            backup_type = "nancy";
            k = 0;
        } else if (algorithm == "UCTIE"){
            trial_expansion = "uct";
            trial_backup = "bfs";
            backup_type = "ie";
        } else if (algorithm == "GUCTIE"){
            trial_expansion = "uct";
            trial_backup = "bfs";
            backup_type = "ie";
            k = 0;
        } else {
            cout << "Invalid algorithm: " << algorithm << endl;
            exit(1);
        }  
    }

    double getLowerConfidence(Node* n)    {
        double mean =  n->getHHatValue();
        if (n->h == mean){
            return n->h;
        }
        double error = mean - n->h;
        double stdDev = error / 2.0;
        double var = pow(stdDev, 2);
        // 1.96 is the Z value from the Z table to get the 2.5 confidence
        return max(n->h, mean - (1.96 * var));
    }
    
    void resetNode(Node* n){
        root->parent = NULL;
        root->successors.clear();
        root->initialized = false;
    }

    ResultContainer getPlan(){
        ResultContainer res;
        State root_state = domain.getStartState();
        res.solutionCost = 0;
        domain.initialize(algorithm, lookahead);

        root = new Node(root_state, w * domain.heuristic(root_state), 1, false, NULL, domain.heuristic(root_state), domain.distance(root_state), 
                            domain.distanceErr(root_state), domain.epsilonHGlobal(), domain.epsilonDGlobal());
        actionVisits[root_state] = 1;

        while(true){
            if (domain.isGoal(root->state)){
                res.solutionFound = true;
                break;
            }

            int exp = res.nodesExpanded;
            unordered_map<State, Node*, Hash> TT;
            TT[root->state] = root;

            // Update epsilons
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
            // dijkstra(TT);

            // Action selection phase
            root = selectOneStepAction(root, TT);
            res.solutionCost += root->edgeCost;
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
        // Change current state h to the sencond best, RTA* style
        // RTA* style, update state to the second best f + edgecost to go back
        // Represents the estimated h cost of solving the problem by returning to this state
        priority_queue<double, vector<double>, greater<double>> minheap;
        double g = n->getGValue();
        for (Node* child : n->successors){
            minheap.push(g + child->edgeCost + child->h);
        } 
        if (minheap.size() > 1){
            minheap.pop();
        }
        domain.updateHeuristic(n->state, minheap.top());

        // TODO
        // domain.updateDistance(s, domain.distance(cur->state) + 1);
        // Update the distance for the heuristic error of this predecessor
        // domain.updateDistanceErr(s, domain.distanceErr(cur->state));
    }

    void dijkstra(unordered_map<State, Node*, Hash> TT){
        // Learning using reverse Dijkstra
        priority_queue<Node*, vector<Node*>, minH> open;
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
    }
   
    void performTrial(unordered_map<State, Node*, Hash>& TT, ResultContainer& res){
        PQueue backUpQueue;
        Node* n = root;
        while (n->initialized){           
            State old = n->state;
            n = selectTrialAction(n, TT);
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
		double best_f = numeric_limits<double>::infinity();

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
                // n'
                Node* childNode = new Node(child, w * domain.heuristic(child), 1, false, n,
                                domain.heuristic(child), domain.distance(child), domain.distanceErr(child), 
                                domain.epsilonHGlobal(), domain.epsilonDGlobal());
                childNode->edgeCost = domain.getEdgeCost(child);  
                
                if (backup_type == "nancy"){
                    childNode->value =
                    DiscreteDistribution(100, childNode->h, childNode->getHHatValue(),
						childNode->d, childNode->getHHatValue() - childNode->h).expectedCost();
                } else if (backup_type == "ie"){
                    childNode->value = getLowerConfidence(n);
                }

                //TT[s'] <- n'
                TT[child] = childNode;
                // cout << child << endl;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.insert(childNode);

            } else {
                // State already in the tree, check to see if it's a better path
                if (n->getGValue() + domain.getEdgeCost(child) < TT[child]->getGValue()) {
                    Node* s = (TT[child]);

                    // cout << " Better path:" << endl;
                    // cout << child << endl;
                    // cout << " Old parent:" << endl;
                    // cout << s->parent->state << endl;

                    backUpQueue.push(s->parent);
                    // N(par(TT[s'])) <- N(par(TT[s'])) \ {n'}
                    s->parent->successors.erase(s);
                    s->parent = n;
                    s->state = child; // update label
                    s->edgeCost = domain.getEdgeCost(child);
                    n->successors.insert(s);

                    // cout << " New parent:" << endl;
                    // cout << n->state << endl;
                }
            }


            if (!TT[child]->initialized){
                if (TT[child]->getFValue() < best_f){
                    best_f = TT[child]->getFValue();
                    bestChild = child;
                }
            }
        }
        
         // Learn one-step error
        if (best_f != numeric_limits<double>::infinity()){
            double epsD = (1 + domain.distance(bestChild)) - n->d;
            double epsH = (domain.getEdgeCost(bestChild) + domain.heuristic(bestChild)) - n->h;
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
            double child_value = child->value + k * child->edgeCost;
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

    Node* selectActionUCT(Node* n){
        return selectUCT(n, true);
    }

    Node* selectTrialUCT(Node* n){
        return selectUCT(n, false);
    }

    Node* selectUCT(Node* n, bool action){
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
            double child_value = child->value + k * child->edgeCost;

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

            int self_visits = n->visits;
            int child_visits = child->visits;

            if (action){
                if (actionVisits.find(n->state) == actionVisits.end()){
                    actionVisits[n->state] = 1;
                } 
                self_visits = actionVisits[n->state];
                if (actionVisits.find(child->state) == actionVisits.end()){
                    child_visits = 1;
                } else {
                    child_visits = actionVisits[child->state];
                }

            }

            double csq = (C * sqrt(log(self_visits)/child_visits));

            if (denom != 0){
                fb = (children_fbar[i] - min)/denom;
            }

            child_value = fb - csq;

            // cout << "  value: " << child->value;
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

        int r = rand() % ties.size();

        if (action){
            if (actionVisits.find(ties[r]->state) == actionVisits.end()){
                actionVisits[ties[r]->state] = 1;
            } else {
                actionVisits[ties[r]->state] += 1;
            }
        }
        return ties[r];
    }

    Node* selectOneStepAction(Node* n, unordered_map<State, Node*, Hash>& TT){
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return n;
        }
        // Min queue to be used for tie breaking
        if (decision == "nancy"){
            priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<pair<double, Node*>> > open; 
            for (auto it : TT){
                // Nodes that are initialized are equivalent to them being in the closed list
                if (!it.second->initialized){
                    DiscreteDistribution d = DiscreteDistribution(100, it.second->getFValue(), it.second->getFHatValue(),
						    it.second->d, it.second->getFHatValue() - it.second->getFValue());
                    open.push(make_pair(d.expectedCost(), it.second));
                }
            }
            Node* cur = open.top().second;
            while(cur->parent != root){
                cur = cur->parent;
            }
            return cur;
        } else if (decision == "minimin") {
            priority_queue<Node*, vector<Node*>, minF> open;
            for (auto it : TT){
                // Nodes that are initialized are equivalent to them being in the closed list
                if (!it.second->initialized){
                    open.push(it.second);
                }
            }
            Node* cur = open.top();
            while(cur->parent != root){
                cur = cur->parent;
            }
            return cur;
        } else if (decision == "ie") {
            priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<pair<double, Node*>> > open; 
            for (auto it : TT){
                // Nodes that are initialized are equivalent to them being in the closed list
                if (!it.second->initialized){
                      open.push(make_pair(getLowerConfidence(it.second), it.second));
                }
            }
            Node* cur = open.top().second;
            while(cur->parent != root){
                cur = cur->parent;
            }
            return cur;
        } else {
            if (trial_expansion == "bfs"){
                return selectBFS(n);
            } else if (trial_expansion == "uct"){
                return selectActionUCT(n);
            } else {
                cout << "Invalid decision algorithm: " << decision << endl;
                exit(1);
            }  
        }


    }
    
    Node* selectTrialAction(Node* n, unordered_map<State, Node*, Hash>& TT){
        // cout << "Select action:" << endl;
        // If there's only one child   
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return n;
        }
        // Min queue to be used for tie breaking
        if (trial_expansion == "bfs"){
            return selectBFS(n);
        } else if (trial_expansion == "uct"){
            return selectTrialUCT(n);
        } else {
            cout << "Invalid algorithm: " << algorithm << endl;
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
            // Backing up the best h value if k = 0
            // Backing up the best f value if k = 1
            double best_value = numeric_limits<double>::infinity();
            for (Node* child : n->successors){
                // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
                double child_value = child->value + k * child->edgeCost;
                if (child_value < best_value){
                    best_value = child_value;
                }
                visits += child->visits; // v(n) <- sum of n' in N(n) {v(n')}
                lock = lock && child->lock; // l(n) <- bools of n' in N(n) {l(n')}
            }
            n->value = best_value;
        } else if (trial_backup == "uct"){
            // Backing up the best estimated h value if k = 0
            // Backing up the best estimated f value if k = 1
            double value = 0;
            for (Node* child : n->successors){
                value += child->visits * (child->value + k * child->edgeCost);
                visits += child->visits;
                lock = lock && child->lock;
            }
            n->value = value/visits;
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
    double C = 1.414; // exploration parameter C
    bool goal_found = false;
    Node* root;
    string decision;
    string algorithm;
    string trial_expansion;
    string trial_backup;
    string backup_type;
    string prune_type = "erase"; // default to removing deadends
    unordered_map<State, int, Hash> actionVisits;
    bool record_plan = true;
};