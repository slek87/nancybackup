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
        double g; // TODO Path costs from root node to a node is g(n). It is not stored, but calculated on demand
        int visits; // Number of visits
        bool lock; // Lock
		Node* parent;
        bool initialized;
        
        double h;
        double d;
        double derr;
        double epsH;
        double epsD;
        Node* bestKNode; // Points to the best sucessor in the open list

    public:
        Node(State state, double val, int visit, bool lock, Node* parent) : state(state), fval(val), visits(visit), lock(lock), parent(parent){
            initialized = false;
            g = 0;
            bestKNode = NULL;
        }

        double getGValue() const { return g; }
		double getHValue() const { return h; }
		double getDValue() const { return d; }
        double getFValue() const { return g + h; }
        double getFHatValue() const { return g + getHHatValue(); }
        double getDHatValue() const { return (derr / (1.0 - epsD)); }
        double getHHatValue() const { return h + getDHatValue() * epsH; }
    };

    struct compare_g {
        bool operator()(const Node* n1, const Node* n2){
            if (n1->g  == n2->g){
                return rand() % 2;
            }
            return n1->g > n2->g;
        }
    };

    struct compare_fhat {
        bool operator()(const Node* n1, const Node* n2){
			if (n1->getFHatValue() == n2->getFHatValue()){
				return rand() % 2;
			}
			return n1->getFHatValue() > n2->getFHatValue();
        }
    };

    typedef priority_queue<Node*, vector<Node*>, compare_g> PQueue;
    
    THTS_RT(Domain& domain, string algorithm, int lookahead)  : domain(domain), algorithm(algorithm), lookahead(lookahead){
        srand(1);
        // Default:
        // w = 1;
        // k = 1;
        // C = 1.4; 
        if (algorithm == "AS"){

        } else if (algorithm == "WAS"){
            w = 5;
        } else if (algorithm == "UCT"){

        } else if (algorithm == "GUCT"){
            k = 0;
        } else if (algorithm == "UCTS"){

        } else if (algorithm == "GUCTS"){
            k = 0;
        }  else if (algorithm == "GUCTS-F"){
            action = "best-f";
            algorithm = "GUCTS";
            k = 0;
        } else if (algorithm == "GUCTS-N"){
            // Greedy UCT expansion with Nancy backup and 
            action = "nancy";
            algorithm = "GUCTS";
            k = 0;
        } else if (algorithm == "GUCTS-B"){
            // Greedy UCT expansion with Nancy backup and 
            action = "bellman";
            algorithm = "GUCTS";
            k = 0;
        }else {
            cout << "Invalid algorithm: " << algorithm << endl;
            exit(1);
        }  
    }
    
    // Info needed for Nancy Backup
    void nacyNodeUpdate(Node* n, double h, double d, double derr, double epsH, double epsD){
        n->d = d;
        n->h = h;
        n->derr = derr;
        n->epsH = epsH;
        n->epsD = epsD;
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
        domain.initialize(algorithm, lookahead);
        ResultContainer res;
        State root_state = domain.getStartState();
        root = new Node(root_state, w * domain.heuristic(root_state), 1, false, NULL);
        if (action == "nancy" || action == "bellman"){
            nacyNodeUpdate(root, 0, domain.distance(root_state), 
                            domain.distanceErr(root_state), domain.epsilonHGlobal(), domain.epsilonDGlobal());
            openList.insert(root);
        }

        if (algorithm == "GUCTS-F" || algorithm == "GUCTS-B" || algorithm == "GUCTS-N"){
            algorithm = "GUCTS";
        }

        int t = 0;
        while(t < max_time){     
            if (domain.isGoal(root->state)){
                res.solutionCost = root->g;
                res.solutionFound = true;
                break;
            }

            int exp = res.nodesExpanded;
            unordered_map<State, Node*, Hash> TT;
            TT[root->state] = root;

            // Expansion phase

            if (action == "nancy" || action == "bellman"){
                domain.updateEpsilons();
            }

            while (res.nodesExpanded - exp < lookahead){
                performTrial(TT, res);
                if (goal_found){
                    goal_found = false;
                    break;
                }
            }
            
            // TODO RTA* style, update state to the second best heuristic + edgecost
            // Change current state h to the sencond best, RTA* style
            // Does not work well with little lookahead
            priority_queue<double, vector<double>, greater<double>> minheap;
            for (Node* child : root->successors){
                minheap.push(root->g + domain.getEdgeCost(child->state) + domain.heuristic(child->state));
                // minheap.push(root->fval);
            } 
            if (minheap.size() > 1){
                minheap.pop();
            }
            domain.updateHeuristic(root->state, minheap.top());
            
            // Action selection phase
            if (action == "best-f"){
                root = selectActionOnBestF(root);
            } else if (action == "nancy"){
                root = selectActionNancy(root);
                openList.clear();
                openList.insert(root);
            } else if (action == "bellman"){
                root = selectActionBellman(root);
                openList.clear();
                openList.insert(root);
            }else {
                root = selectAction(root);
            }

            root->parent = NULL;
            root->successors.clear();
            root->initialized = false;
            
            // Add this step to the path taken so far
            res.path.push(root->state.getLabel());
	
            ++t;
            for (auto it : TT){
                if (it.second != root){
                    delete(it.second);
                }
            }
        }

        delete(root);

        if (t == max_time){
            cout << "Time limit reached." << endl;
            res.solutionFound = false;
        }

        return res;
    }

    void performTrial(unordered_map<State, Node*, Hash>& TT, ResultContainer& res){
        PQueue backUpQueue;
        Node* n = root;
        while (n->initialized){           
            State old = n->state;
            n = selectAction(n);
            if (old == n->state){
                cout << "Deadend..." << endl;
                exit(1);
            }
            // cout << "At:\n" << n->state << "\n" << endl;
        }

        // If n is goal
        // TODO perhaps keep expanding until expansion limit even when the goal is found 
        // in case a better path is found. Rightnow, just want to finish implementation. 
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
            // TODO not sure how to check deadend just yet
            if (it == TT.end()){
                // Node(State state, int N, Cost f, int v, Node* parent)
                // n' <- <s', 0, w*h(s'), l, isGoal(s')>
                // Node* childNode(new Node(child, w * domain.heuristic(child), 1, domain.isGoal(child), n)); // n'


                // TODO, don't lock the child if it's goal even when the paper says to
                Node* childNode = new Node(child, w * domain.heuristic(child), 1, false, n); // n'
                
                // childNode->g = pathCost(childNode);    // TODO this was not supposed to be stored in the node
                childNode->g = n->g + domain.getEdgeCost(child);
                
                // Added for Nancy backup
                if (action == "nancy" || action == "bellman"){
                    nacyNodeUpdate(childNode, domain.heuristic(child), domain.distance(child), domain.distanceErr(child), 
                                    domain.epsilonHGlobal(), domain.epsilonDGlobal());
                    if (childNode->getFValue() < bestF){
                        bestF = childNode->getFValue();
                        bestChild = child;
                    }
                    openList.insert(childNode);
                }

                //TT[s'] <- n'
                TT[child] = childNode;

                // cout << "  childfval: " << childNode->fval << endl;
                // cout << child << endl;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.insert(childNode);


            } else {
                // State already in the tree, check to see if it's a better path
                // if (n->g + domain.getEdgeCost(child) < pathCost(TT[child])) {
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
        }
        
        if (action == "nancy" || action == "bellman"){
            openList.erase(n);

            // Learn one-step error
            if (bestF != numeric_limits<double>::infinity()){
                double epsD = (1 + domain.distance(bestChild)) - n->getDValue();
                double epsH = (domain.getEdgeCost(bestChild) + domain.heuristic(bestChild)) - n->getHValue();
                domain.pushEpsilonHGlobal(epsH);
                domain.pushEpsilonDGlobal(epsD);
            }
        }

        n->initialized = true;
    }

    Node* selectActionOnBestF(Node* n){
        // cout << "Select action:" << endl;

        // TODO should only be selecting a child that's not locked. But it doesn't make 

        // If there's only one child   
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return n;
        }

        // THTS-BFS
        // return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
        // i.e. return successor that is not locked with the lowest value
        double best_value = numeric_limits<double>::infinity();
        for (Node* child : n->successors){
            if (prune_type == "lock" && child->lock){
                continue;
            }
            double child_value = child->fval + domain.getEdgeCost(child->state);
            if (child_value <= best_value){
                if (child_value == best_value){
                    if (rand() % 2){
                        n = child;
                    }
                } else {
                    best_value = child_value;
                    n = child;
                }
            }
        }
        return n;
    }

    Node* selectActionBellman(Node* n){
        // If there's only one child   
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return n;
        }

        priority_queue <Node*, vector<Node*>, compare_fhat> pqueue;
        for (Node* node : openList){
            pqueue.push(node);
        } 
        
        Node* best = pqueue.top();

        while (best->parent != root){
            best = best->parent;
        }

        n = best;
        return n;
    }   

    Node* selectActionNancy(Node* n){
        // If there's only one child   
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return n;
        }

        for (Node* node : openList){
            node->bestKNode = node;
        }

        // Iterate through the open list and update bestKNode
        // i.e. back up frontier's nodes values to the TLA nodes
        for (Node* node : openList){
            Node* cur = node->parent;
            // Push kBest node up to TLA node
            while(cur != root){
                if (cur->bestKNode){
                    // Check to see which f hat is better, push that one up
                    if (cur->bestKNode->getFHatValue() == node->getFHatValue()){
                        // Tie break on g-value
                        if (node->getGValue() < cur->bestKNode->getGValue()){
                            cur->bestKNode = node;
                        } else {
                            break;
                        }
                    } else {
                        if (node->getFHatValue() < cur->bestKNode->getFHatValue()){
                            cur->bestKNode = node;
                        } else {
                            break;
                        }
                    }
                } else {
                    cur->bestKNode = node;
                }
                cur = cur->parent;
            }
        }

        // At this point, all TLA nodes will have the k-best frontire node
        double best_value = numeric_limits<double>::infinity();
        for (Node* child : n->successors){
            DiscreteDistribution d = DiscreteDistribution(100, child->bestKNode->getFValue(), child->bestKNode->getFHatValue(),
						    child->bestKNode->getDValue(), child->bestKNode->getFHatValue() - child->bestKNode->getFValue());
            double expectedMinimumPathCost = d.expectedCost();
            if (expectedMinimumPathCost < best_value){
                best_value = expectedMinimumPathCost;
                n = child;
            }
        }
        n->bestKNode = NULL;
        return n;
    }

    Node* selectAction(Node* n){
        // cout << "Select action:" << endl;

        // TODO should only be selecting a child that's not locked. But it doesn't make 

        // If there's only one child   
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return n;
        }

        if (algorithm == "AS" || algorithm == "WAS"){
            // THTS-BFS
            // return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
            // i.e. return successor that is not locked with the lowest value
            double best_value = numeric_limits<double>::infinity();
            for (Node* child : n->successors){
                if (prune_type == "lock" && child->lock){
                    continue;
                }
                double child_value = child->fval + k * domain.getEdgeCost(child->state);
                if (child_value <= best_value){
                    if (child_value == best_value){
                        if (rand() % 2){
                            n = child;
                        }
                    } else {
                        best_value = child_value;
                        n = child;
                    }
                }
            }
        } else if (algorithm == "UCT" || algorithm == "GUCT" || algorithm == "UCTS" || algorithm == "GUCTS"){
            // UTC
            double best_value = numeric_limits<double>::infinity();
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

                if (child_value <= best_value){
                    if (child_value == best_value){
                        if (rand() % 2){
                            n = child;
                        }
                    } else {
                        best_value = child_value;
                        n = child;
                    }
                }
                ++i;
            }
        }

        return n;
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
        if (algorithm == "AS" || algorithm == "WAS" || algorithm == "UCTS" || algorithm == "GUCTS" ){
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
        } else if(algorithm == "UCT" || algorithm == "GUCT"){
            double fval = 0;
            for (Node* child : n->successors){
                fval += child->visits * (child->fval + k * domain.getEdgeCost(child->state));
                visits += child->visits;
                lock = lock && child->lock;
            }
            n->fval = fval/visits;

            // cout << "  new fval: " << n->fval << endl;
        } else {
            cout << "Invalid backup algorithm: " << algorithm << endl;
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

    void setPruning(string type){
        prune_type = type;
    }

protected:
    Domain& domain;
    int max_time = 5000000;
    double w = 1;
    double k = 1;
    int lookahead;
    double C = 1.4; // exploration parameter C
    bool goal_found = false;
    Node* root;
    string algorithm;
    string prune_type = "erase"; // default to removing deadends
    string action;
    unordered_set<Node*> openList;
};