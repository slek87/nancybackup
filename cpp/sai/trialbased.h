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
        int visits; // Number of visits.
        bool lock; // Lock.
		Node_ptr parent;
        bool initialized;

    public: 
        Node(State state, double val, int visit, bool lock, Node_ptr parent, bool init)
			: state(state), value(val), visits(visit), lock(lock), parent(parent), initialized(init){
        }    
        
    };
    
    typedef shared_ptr<Node> Node_ptr;

    struct compare_f {
        bool operator()(const Node_ptr lhs, const Node_ptr rhs){
            return lhs->g + lhs->h  > rhs->g + rhs->h;
        }
    };
    
    typedef priority_queue<Node_ptr, vector<Node_ptr>, compare_f> PQueue; 


    THTS(Domain& domain) : domain(domain) {
        State root_state = domain.getStartState();  
        root.reset(new Node(root_state, w * domain.heuristic(root_state), 1, false, NULL, false));
    }

    void getPlan(){
        // while time allows and no plan found do
        int t = 0;
        while (t < 100 && plan_found == false){
            performTrial();
        }
    }

    void performTrial(){
        // PriorityQueue<Node*> backupQueue;
        PQueue backupQueue; 
        Node_ptr n = root;
        while (n->initialized){
            selectAction(n);
        }

        // If n is goal
        if (domain.isGoal(n->state)){
            return; // Extract plan and return
        }

        initalizeNode(n, backupQueue);
    }
    
    void selectAction(Node_ptr n){
        // THTS-BFS
        // return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
        // ie return successor that is not locked with the lowest value
		double best_value = numeric_limits<double>::infinity();
        for (Node_ptr child : n->successors){
            if (child->lock == false){
                double child_value = child->value + k * domain.getEdgeCost(child->state);
                if (child_value < best_value){
                    best_value = child_value;
                    n = child;
                }
            }
        }

        // UTC
    }

    void initalizeNode(Node_ptr n, PQueue& backupQueue){
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
                Node_ptr childNode(new Node(child, w * domain.heuristic(child), 1, 
                                domain.isGoal(child), n, false)); // n'
                
                //TT[s'] <- n'
                TT[child] = childNode;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.insert(childNode);
            }
        }

    }

    double pathCost(Node_ptr n){
        return 0.0;
    }

	protected:
        Domain & domain;
        int max_time = 100;
        int w = 1;
        int k = 1;
        bool plan_found = false;
        Node_ptr root;
        unordered_map<State, Node_ptr, Hash> TT;

};