#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <limits>
#include <math.h>

using namespace std;

template <class Domain>
class THTS{
    typedef typename Domain::State State;
    typedef typename Domain::Cost Cost;
    typedef typename Domain::HashState Hash;

public:
    struct Node {
        State state; // State
        unordered_set<shared_ptr<Node>> successors; // Children
        double fval; // Name this value something
        double g; // TODO Path costs from root node to a node is g(n). It is not stored, but calculated on demand
        int visits; // Number of visits
        bool lock; // Lock
		shared_ptr<Node> parent;
        bool initialized;

    public: 
        Node(State state, double val, int visit, bool lock, shared_ptr<Node> parent) : state(state), fval(val), visits(visit), lock(lock), parent(parent){
            initialized = false;
            g = 0;
        }
    };

    struct compare_g {
        bool operator()(const shared_ptr<Node> lhs, const shared_ptr<Node> rhs){
            // return lhs->g + lhs->h  > rhs->g + rhs->h;
            return lhs->g > rhs->g;
        }
    };

    typedef priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, compare_g> PQueue; 

    double pathCost(shared_ptr<Node>& n){
        double g = 0;
        shared_ptr<Node> cur = n;
        while (cur->parent){
            g +=  domain.getEdgeCost(cur->state);
            cur = cur->parent;
        }
        return g;
    }

    THTS(Domain& domain, string algorithm) : domain(domain), algorithm(algorithm){
        State root_state = domain.getStartState();  
        root.reset(new Node(root_state, w * domain.heuristic(root_state), 1, false, NULL));
        TT[root_state] = root;
    }

    void getPlan(){
        // While time allows and no plan found do
        // TODO in my case, it will be the max look ahead
        int t = 0;
        while (t < max_time && goal_found == false){
            performTrial();
            ++t;
        }
    }
    
    void performTrial(){
        cout << "Perform Trial:_______________________________________" << endl;

        PQueue backupQueue; 
        shared_ptr<Node> n = root;

        while (n->initialized){
            selectAction(n);
            cout << "At:\n" << n->state << "\n" << endl;
        }

        // If n is goal
        if (domain.isGoal(n->state)){
            goal_found = true;
            return; // Extract plan and return
        }

        initalizeNode(n, backupQueue);
        if (n) backupQueue.push(n);

        // while backupQueue is not empty do
        while (!backupQueue.empty()){
            n = backupQueue.top(); // m <-backupQueue.pop()
            backupQueue.pop();
            backUp(n);
            
            if (n != root){
                backupQueue.push(n->parent);
            }

        }
    }
    
    void initalizeNode(shared_ptr<Node>& n, PQueue& backupQueue){
        cout << "Initalize:\n" << n->state << "\n" << endl;

        vector <State> children = domain.successors(n->state);
        // For each action... In this case for each children
        for (State child : children){    
            // child = s'
            auto it = TT.find(child);

            // If s' not in TT and not is not deadend then
            // TODO not sure how to check deadend just yet
            if (it == TT.end()){
                // Node(State state, int N, Cost f, int v, Node* parent)
                // n' <- <s', 0, w*h(s'), l, isGoal(s')>
                shared_ptr<Node> childNode(new Node(child, w * domain.heuristic(child), 1, domain.isGoal(child), n)); // n'
                
                childNode->g = pathCost(childNode);    // TODO this was not supposed to be stored in the node

                //TT[s'] <- n'
                TT[child] = childNode;

                // cout << "  childfval: " << childNode->fval << endl;
                // cout << child << endl;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.insert(childNode);
            } else {
                // State already in the tree, check to see if it's a better path
                if (n->g + domain.getEdgeCost(child) < pathCost(TT[child])) {
                    shared_ptr<Node> s = (TT[child]);
                    backupQueue.push(s->parent);
                    // N(par(TT[s'])) <- N(par(TT[s'])) \ {n'}
                    s->parent->successors.erase(s);
                    s->parent = n;
                    s->g = n->g + domain.getEdgeCost(child);
                    s->state = child; // update label
                    n->successors.insert(s);
                }
            }
        }
        n->initialized = true;
    }

    void selectAction(shared_ptr<Node>& n){   
        cout << "Select action:" << endl;

        // TODO should only be selecting a child that's not locked. But it doesn't make 

        // If there's only one child   
        if (n->successors.size() == 1){
            n = *(n->successors.begin());
            return;
        }

        if (algorithm == "BFS"){
            // THTS-BFS
            // return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
            // i.e. return successor that is not locked with the lowest value
            double best_value = numeric_limits<double>::infinity();
            for (shared_ptr<Node> child : n->successors){
                double child_value = child->fval + k * domain.getEdgeCost(child->state);
                if (child_value < best_value){
                    best_value = child_value;
                    n = child;
                }
            }
        } else if (algorithm == "UCT"){
            // UTC
            double best_value = numeric_limits<double>::infinity();
            double min = numeric_limits<double>::infinity();
            double max = 0;
            vector <double> children_fbar;

            // Finiding the max and min to use for normalization
            for (shared_ptr<Node> child : n->successors){
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
            for (shared_ptr<Node> child : n->successors){
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

                if (child_value < best_value){
                    best_value = child_value;
                    n = child;
                }
                ++i;
            }
        } else {
            cout << "Invalid algorithm: " << algorithm << endl;
            exit(1);
        }
    }

    void backUp(shared_ptr<Node>& n){
        // cout << "Back up:\n" << n->state << endl;

        if (n->successors.size() == 0){
            n->parent->successors.erase(n);
            cout << "  Dead end!" << endl;
            cout << "  Parent's succ size: " << n->parent->successors.size();
            return;
        }

        int visits = 0;
        bool lock = true;
        if (algorithm == "BFS"){
            // THTS-BFS
            double best_value = numeric_limits<double>::infinity();
            for (shared_ptr<Node> child : n->successors){
                // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
                double child_value = child->fval + k * domain.getEdgeCost(child->state);
                if (child_value < best_value){
                    best_value = child_value;   
                }
                visits += child->visits; // v(n) <- sum of n' in N(n) {v(n')}
                lock = lock && child->lock; // l(n) <- bools of n' in N(n) {l(n')}
            }
            n->fval = best_value;
        } else if(algorithm == "UCT"){
            double fval = 0;
            for (shared_ptr<Node> child : n->successors){
                fval += child->visits * (child->fval + k * domain.getEdgeCost(child->state));
                visits += child->visits;
                lock = lock && child->lock;
            }
            n->fval = fval/visits;

            // cout << "  new fval: " << n->fval << endl;
        } else {
            cout << "Invalid algorithm: " << algorithm << endl;
            exit(1);
        }

        n->visits = visits;
        n->lock = lock;
    }

protected:
    Domain & domain;
    int max_time = 1000000;
    int w = 5;
    int k = 0;
    double C = 1.4; // exploration parameter C
    bool goal_found = false;
    shared_ptr<Node> root;
    unordered_map<State, shared_ptr<Node>, Hash> TT;
    string algorithm; 
};