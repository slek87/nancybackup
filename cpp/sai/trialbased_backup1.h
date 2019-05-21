#pragma once
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set> 
#include"../utility/ResultContainer.h"
// #include "../utility/PriorityQueue.h"

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
        unordered_set<Node*> successors; // Children.
        double value; // Name this value something
        int visits; // Number of visits.
        bool lock; // Lock.
		Node* parent;
        bool initialized;

    public: 
        Node(State state, double val, int visit, bool lock, Node* parent, bool init)
			: state(state), value(val), visits(visit), lock(lock), parent(parent), initialized(init){}

    };

    ~THTS(){
        for(auto it : TT){
            delete(it.second);
        }
    }

    THTS(Domain& domain) : domain(domain) {
        k = 1; // TODO
        w = 1; // TODO
        //  State state, double val, int visit, bool lock, Node* parent, bool init
        initial_node = new Node(domain.getStartState(), 
            w * domain.heuristic(domain.getStartState()), 1, false, NULL, false); // n <- n_0 
        TT[domain.getStartState()] = initial_node;
        start_state = domain.getStartState();   
        goal_node = NULL;
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

    void initalizeNode(Node* n,  priority_queue<pair<double, Node*>>& backupQueue){
        if (DEBUG) cout << "Init " << n->state << endl;
        vector <State> children = domain.successors(n->state);
        
        res.nodesExpanded++;
        State bestChild;
		double best_value = numeric_limits<double>::infinity();

        // for each action... In this case for each children
        for (State child : children){    
            // child = s'
            auto it = TT.find(child);

            // If s' not in TT and not is not deadend then
            if (it == TT.end()){
                // Node(State state, int N, Cost f, int v, Node* parent)
                // n' <- <s', 0, w*h(s'), l, isGoal(s')>

                // State state, double val, int visit, bool lock, Node* parent, bool init
                Node* childNode = new Node(child, w * domain.heuristic(child), 1, domain.isGoal(child), n, false); // n'
                res.nodesGenerated++;

                //TT[s'] <- n'
                TT[child] = childNode;

                //N(n) <- N(n) union {n'} N = succesor nodes
                n->successors.insert(childNode);
                if (DEBUG) cout << "Adding to TT " << childNode->state << " | Parent: " << childNode->parent->state << endl;
                if (domain.isGoal(child)){
                    if (DEBUG) cout << "Goal Child" << endl;
                    if (!goal_node){
                        goal_node = childNode;
                    } else {
                        if (pathCost(goal_node) > pathCost(childNode)) goal_node = childNode;
                    }
                }

            // Else if g(n) + c(o) < g(TT[s'])
            } else {
                if (DEBUG) cout << "Already in table " << child << " | Parent: " << TT[child]->parent->state << endl;

                if (pathCost(n) + domain.getEdgeCost(n->state) < pathCost(TT[child])) {
                    if (DEBUG) cout << "but found a better path" << endl;
                    // TT[s']
                    Node * s = (TT[child]);


                    // N(par(TT[s'])) <- N(par(TT[s'])) \ {n'}
                    s->parent->successors.erase(s);

                    // g(TT[s']) = g(n) + c(o) 
                    double g = pathCost(n) + domain.getEdgeCost(child);
                    
                    // N(n) <- N(n) union {TT[s']}
                    n->successors.insert(s);
                    if (DEBUG) cout << "adding " << s->state << " to " << n->state << endl;

                    // the actual algo has this in the begining of this block
                    // but moved here so the queue will be correct
                    // since std heap does not push up when upding value inside
                    // the heap
                    // backupQueue.insert(par(TT[s']))
                    backupQueue.push(make_pair(g, s->parent));
                }
            }
        }

        n->initialized = true;

    }


    void backUp(Node* n){
        if (DEBUG) cout << "Backing up " << n->state << endl;

        // THTS-BFS
        double best_value = numeric_limits<double>::infinity();
        int visits = 0;
        bool lock = true;
        for (Node* child : n->successors){
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

    Node* selectAction(Node* n){
        // THTS_BFS: return arg min n' in N(n) that is not locked minizing: f(n') + k * c(n, n')
        // f(n) <- min_[n' in N(n)]{ f(n') + k * c(n, n') }
		double best_value = numeric_limits<double>::infinity();
        Node* best_child = NULL;
        for (Node* child : n->successors){
            if (child->lock == false){
                double child_value = child->value + k * domain.getEdgeCost(child->state);
                if (child_value < best_value){
                    best_value = child_value;
                    best_child = child;
                }
            } else {

            }
            if (DEBUG) cout << "  " << child->state << " val:" << child->value + k * domain.getEdgeCost(child->state);
            if (DEBUG) cout << " l:" << child->lock << endl;
        }
        return best_child;
    }

    void performTrial(){
        // PriorityQueue<Node*> backupQueue;
        priority_queue< pair<double, Node*> > backupQueue; 
        Node* n = initial_node; // n <- n_0

        if (DEBUG && n->initialized) cout << "Selecting action" << endl;

        unordered_set<Node*> dub;

        while (n->initialized){

            if (DEBUG) cout << n->state << endl;
            n = selectAction(n);
            // All the children have been locked
            if (!n) return;
            if (DEBUG) cout << n->state << " " << n->state.getLabel() << endl;
            
            auto it = dub.find(n);
            if (it != dub.end()) return;
            

            dub.insert(n);
        }
        // If n is goal
        if (domain.isGoal(n->state)){
            if (DEBUG) cout << "GOAL" << endl;
            return; // Extract plan and return
        }
       
        initalizeNode(n, backupQueue);

        backupQueue.push(make_pair(pathCost(n), n));

        // while backupQueue is not empty do
        while (!backupQueue.empty()){
            n = backupQueue.top().second; // m <-backupQueue.pop()
            backupQueue.pop();

            // trial finished when backup is called on root
            if (n == initial_node) return;

            backUp(n);

            // if n != n_0
            //   backupQueue.insert(part(n))
            if (n->state != start_state){
                backupQueue.push(make_pair(pathCost(n->parent), n->parent));
            }
        }

    }

    ResultContainer solve(int trials){
        // while time allows and no plan found do
        // TODO for now give infinite time
        for(int i = 0; i < trials; ++i){
            if (DEBUG) cout << "\n----------------------------------------\nTrail " << i << endl;
            performTrial();
        }

        if (goal_node){
            res.solutionFound = true;
		    res.solutionCost = pathCost(goal_node);
        }

        return res;

    }

    ResultContainer solve(){
        // while time allows and no plan found do
        // TODO for now give infinite time
        // int trials = 16;
        // for(int i = 0; i < trials; ++i){
        //     if (DEBUG) cout << "\n----------------------------------------\nTrail " << i << endl;
        //     performTrial();
        // }
        int i = 0;
        while (!goal_node)  performTrial(); if (DEBUG) cout << "\n----------------------------------------\nTrail " << i++ << endl; 
        // return plan

        if (goal_node){
            res.solutionFound = true;
		    res.solutionCost = pathCost(goal_node);
            // double g = 0;
            // Node* cur = goal_node;
            // while (cur->parent){
            //     g +=  domain.getEdgeCost(cur->state);
            //     cur = cur->parent;
            // }
        }

        return res;
    }

    void printPlan(){
        if (goal_node){
            string goal_state = goal_node->state.toString();

            if (domain.getDomainName() == "PancakePuzzle" || domain.getDomainName() == "PancakePuzzleDPS"){
                vector <int> plan;
                cout << "*Tracing from goal to starting starting:" << endl;
                while (goal_node->parent){
                    plan.push_back(goal_node->state.getLabel());
                    cout << goal_node->state << endl;
                    goal_node = goal_node->parent;
                }
                cout << goal_node->state << endl;
                cout << "*End trace. Printing plan:" << endl;

                cout << "# " << goal_node->state.toString();
                for (int i = plan.size() - 1; i >= 0; --i){
                    cout << plan[i] << endl;
                }
                cout << "# " << goal_state;
                cout << endl;

            } else {

                vector <char> plan;
                cout << "*Tracing from goal to starting starting:" << endl;
                while (goal_node->parent){
                    plan.push_back(goal_node->state.getLabel());
                    cout << goal_node->state << endl;
                    goal_node = goal_node->parent;
                }
                cout << goal_node->state << endl;
                cout << "*End trace. Printing plan:" << endl;

                cout << "# " << goal_node->state.toString();
                for (int i = plan.size() - 1; i >= 0; --i){
                    cout << plan[i] << endl;
                }
                cout << "# " << goal_state;
                cout << endl;

            }

        } else {
            cout << "No Goal." << endl;
        }
    }

    void debug(bool b){
        DEBUG = b;
    }

    void setW(int i){
        w = i;
    }

    void setK(int i){
        k = i;
    }

	protected:
        ResultContainer res;
        unordered_map<State, Node*, Hash> TT;
        State start_state;
        Node* initial_node;
        Node* goal_node;
		double k;
        double w;

        double lookahead;

        Domain & domain;
        bool DEBUG = false;
};