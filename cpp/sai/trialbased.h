#pragma once
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <limits>
#include"../utility/ResultContainer.h"
#include "../utility/PriorityQueue.h"

using namespace std;

template <class Domain>
class THTS{
    public:
        typedef typename Domain::State State;
        typedef typename Domain::Cost Cost;
        typedef typename Domain::HashState Hash;

    struct Node {
        // Path costs from root node to a node is g(n)
        // It is not stored, but calculated on demand

        State state; // State.
        vector<Node*> successors; // Children.
        Cost value;
        int visits; // Number of visits.
        bool lock; // Lock.
		Node* parent;
        bool initialized;

    public:
        Node* getParent() const {return parent;}
        State getState() const {return state;}
        int getVisits() const {return visits;}
        bool getLock() const {return lock;}
        bool getInit() const {return initialized;}

        void setParent(Node* p) { parent = p; }
    
        Node(State state, Cost f, Cost g, Cost h, int v, bool l, Node* parent, bool i)
			: state(state), f(f), g(g), h(h), visits(v), lock(l), parent(parent), initialized(i){}

        static bool compare(const Node* n1, const Node* n2) {
			// Tie 
			if (n1->g == n2->g)
			{
				return n1->g > n2->g;
			}
			return n1->g < n2->g;
		}
    };

    THTS(Domain& domain) : domain(domain) {
        k = 1; // TODO
        w = 1; // TODO
        backupQueue.swapComparator(Node::compare);
        //  state(state), f(f), g(g), h(h), visits(v), lock(l), parent(parent), initialized(i)
        Node* initial_node = new Node(domain.getStartState(), 0, 0, domain.heuristic(domain.getStartState()), 1, false, NULL, false); // n <- n_0 
        start_state = domain.getStartState();   
    }

    Cost pathCost(Node* n){
        Cost g = 0;
        Node* cur = n;
        while (cur->parent){
            g +=  domain.getEdgeCost(n->getState());
            cur = cur->getParent();
        }
        return g;
    }

    void initalizeNode(Node* n){
        vector <State> children = domain.successors(n->getState());

        State bestChild;
		Cost bestF = numeric_limits<double>::infinity();

        // for each action... In this case for each children
        for (State child : children){
            // child = s'
            
            typename unordered_map<State, Node*, Hash>::iterator it = TT.find(child);
            
            // If s' not in TT and not is not deadend then
            if (it == TT.end()){
                // Node(State state, int N, Cost f, int v, Node* parent)
                // n' <- <s', 0, w*h(s'), l, isGoal(s')>

                // state(state), f(f), g(g), h(h), visits(v), lock(l), parent(parent), initialized(i)
                Node* childNode = new Node(child, w * domain.heuristic(child), 0, 0, 1, domain.isGoal(child), n, false); // n'
                //TT[s'] <- n'
                TT[child] = childNode;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.push_back(childNode);

            // Else if g(n) + c(o) < g(TT[s'])
            } else if (pathCost(n) + domain.getEdgeCost(n->getState()) < pathCost(TT[child])) {
                Node * s = (TT[child]);

                // backupQueue.insert(par(TT[s']))
                backupQueue.push(s->getParent());

                // N(par(TT[s'])) <- N(par(TT[s'])) \ {n'}
                vector<Node*> updateparSucc;
                for (Node* succ : s->getParent()->successors){
                    if (succ != s)
                        updateparSucc.push_back(succ);
                }

                s->getParent()->successors = updateparSucc;

                // g(TT[s']) = g(n) + c(o) 
                // TODO don't need this?
                
                // N(n) <- N(n) union {TT[s']}
                n->successors.push_back(s);
                s->setParent(n);
            
            }
        
        }
    }


    void backUp(Node* n){
        // THTS-BFS
        Cost bestF = numeric_limits<double>::infinity();
        int visits = 0;
        bool lock = true;
        for (Node* child : n->successors){
            // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
            Cost childF = child->f + k * domain.getEdgeCost(child->getState());
            if (childF < bestF)
                bestF = childF;
        
            // v(n) <- sum of n' in N(n) {v(n')}
            visits += child->visits;
            
            // l(n) <-
            lock = lock && child->lock;
        }
    }

    Node* selectAction(Node* n){
        // THTS_BFS: return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
        // TODO

        // f(n) <- min_[n' in N(n)]{ f(n') + k * c(n, n') }
        vector <State> children = domain.successors(n->getState());
		Cost bestF = numeric_limits<double>::infinity();
        Node* bestN;

        for (Node* child : n->successors){
            if (child->lock == false){
                Cost childF = child->f + k * domain.getEdgeCost(child->getState());
                if (bestF < childF){
                    bestF = childF;
                    bestN = child;
                }
            }
        }

        return bestN;
    }

    void performTrial(){
        
        Node* n = initial_node; // n <- n_0

        while (n->getInit()){
            n = selectAction(n);
        }

        // If n is goal
        if (domain.isGoal(n->getState()))
            return; // Extract plan and return
        
        initalizeNode(n);

        // backupQueue.insert(n)

        backupQueue.push(n);
        int head_index = 0;

        // while backupQueue is not empty do
        while (head_index < backupQueue.size() ){
            n = backupQueue.top(); // m <-backupQueue.pop()
            backupQueue.pop();

            backUp(n);

            // if n != n_0
            //   backupQueue.insert(part(n))
            if (n->getState() != start_state){
                 backupQueue.push(n->getParent());
            }
        }

    }

    void solve(){
        // while time allows and no plan found do
        // TODO for now give infinite time
        int trials = 10;
        for(int i = 0; i < trials; ++i){
            cout << i << endl;
            performTrial();
        }
        // return plan
    }

	protected:
        unordered_map<State, Node*, Hash> TT;
        PriorityQueue<Node*> backupQueue;
        State start_state;
        Node* initial_node;
		double k;
        double w;
        Domain & domain;
};