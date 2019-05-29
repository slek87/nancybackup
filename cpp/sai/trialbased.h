#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

template <class Domain>
class THTS{
    typedef typename Domain::State State;
    typedef typename Domain::Cost Cost;
    typedef typename Domain::HashState Hash;
    public:

    struct Node {
        typedef shared_ptr<Node> Node_ptr;

        // Path costs from root node to a node is g(n)
        // It is not stored, but calculated on demand
        State state; // State.
        unordered_set<Node_ptr> successors; // Children.
        double value; // Name this value something
        double g;
        int visits; // Number of visits.
        bool lock; // Lock.
		Node_ptr parent;
        bool initialized;

    public: 
        Node(State state, double val, int visit, bool lock, Node_ptr parent)
			: state(state), value(val), visits(visit), lock(lock), parent(parent){
                initialized = false;
                g = 0;
        }     
    };
    
    typedef shared_ptr<Node> Node_ptr;

    struct compare_g {
        bool operator()(const Node_ptr lhs, const Node_ptr rhs){
            // return lhs->g + lhs->h  > rhs->g + rhs->h;
            return lhs->g > rhs->g;

        }
    };
    
    typedef priority_queue<Node_ptr, vector<Node_ptr>, compare_g> PQueue; 

    
    double pathCost(Node_ptr& n){
        double g = 0;
        Node_ptr cur = n;
        while (cur->parent){
            g +=  domain.getEdgeCost(cur->state);
            cur = cur->parent;
        }
        return g;
    }
    

    THTS(Domain& domain) : domain(domain) {
        State root_state = domain.getStartState();  
        root.reset(new Node(root_state, w * domain.heuristic(root_state), 1, false, NULL));
        TT[root_state] = root;

    }



    void getPlan(){
        // while time allows and no plan found do
        int t = 0;
        while (t < max_time && plan_found == false){
            
            // cout << "perform trial" << endl;
            performTrial();
            // cout << "________________" << endl;
            ++t;
        }
    }

    void performTrial(){
        // PriorityQueue<Node*> backupQueue;
        PQueue backupQueue; 
        Node_ptr n = root;
        cout << "ROOT:\n" <<  n->state << endl;

        int i = 0;
        while (n->initialized){
            selectAction(n);
            cout << i++ << " PICK:\n" << n->state << endl;
        }

        // If n is goal
        if (domain.isGoal(n->state)){
            cout << "DONE!" << endl;
            plan_found = true;
            return; // Extract plan and return
        }

        initalizeNode(n, backupQueue);
        backupQueue.push(n);

        // while backupQueue is not empty do
        while (!backupQueue.empty()){
            n = backupQueue.top(); // m <-backupQueue.pop()
            backupQueue.pop();
            backUp(n);
            
            // if n != n_0
            //   backupQueue.insert(part(n))
            if (n != root){
                backupQueue.push(n->parent);
            }

        }
    }

    void backUp(Node_ptr& n){
        // cout << "back up" << endl;
        // cout << n->state << endl;
        // THTS-BFS
        double best_value = numeric_limits<double>::infinity();
        int visits = 0;
        bool lock = true;
        for (Node_ptr child : n->successors){
            // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
            double child_value = child->value + k * domain.getEdgeCost(child->state);
            if (child_value < best_value)
                best_value = child_value;
        
            // v(n) <- sum of n' in N(n) {v(n')}
            visits += child->visits;
            
            // l(n) <-
            lock = lock && child->lock;
        }
        n->value = best_value;
        n->visits = visits;
        n->lock = lock;
    }
    
    void selectAction(Node_ptr& n){
        // cout << "select action" << endl;

        // THTS-BFS
        // return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
        // i.e. return successor that is not locked with the lowest value
		double best_value = numeric_limits<double>::infinity();
        for (Node_ptr child : n->successors){

            // cout << "  ";
            // cout << child->state << endl;

            // if (child->lock == false){
            //     cout << "  not locked" << endl;
                double child_value = child->value + k * domain.getEdgeCost(child->state);
                if (child_value < best_value){
                    best_value = child_value;
                    n = child;
                    // cout << "  picking this child" << endl;
                }
            // }
        }

        // UTC
    }

    void initalizeNode(Node_ptr& n, PQueue& backupQueue){
        // cout << "initalize " << n->state << endl;

        vector <State> children = domain.successors(n->state);

        // for each action... In this case for each children
        for (State child : children){    
            // child = s'
            auto it = TT.find(child);

            // If s' not in TT and not is not deadend then
            // TODO not sure how to check deadend just yet
            if (it == TT.end()){
                // Node(State state, int N, Cost f, int v, Node* parent)
                // n' <- <s', 0, w*h(s'), l, isGoal(s')>
                Node_ptr childNode(new Node(child, w * domain.heuristic(child), 1, domain.isGoal(child), n)); // n'
                childNode->g = pathCost(childNode);           
                //TT[s'] <- n'
                TT[child] = childNode;

                // cout << "  " << child;
                // if (domain.isGoal(child)){
                //     cout << " GOAL";
                // }
                // cout << endl;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.insert(childNode);
            } else {
                if (pathCost(n) + domain.getEdgeCost(n->state) < pathCost(TT[child])) {
                    Node_ptr s = (TT[child]);
                    backupQueue.push(s->parent);

                    // N(par(TT[s'])) <- N(par(TT[s'])) \ {n'}
                    s->parent->successors.erase(s);
                    s->parent = n;
                    s->g = n->g + domain.getEdgeCost(child);
                    n->successors.insert(s);
                }
            }
        }

        n->initialized = true;

    }


	protected:
        Domain & domain;
        int max_time = 1000000;
        int w = 5;
        int k = 1;
        bool plan_found = false;
        Node_ptr root;
        unordered_map<State, Node_ptr, Hash> TT;

};