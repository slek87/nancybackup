#pragma once
#include "trialbased.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <limits>
#include <math.h>
#include "../utility/ResultContainer.h"

using namespace std;

template <class Domain> class THTS_RT : public THTS <Domain>{
    typedef typename Domain::State State;
    typedef typename Domain::Cost Cost;
    typedef typename Domain::HashState Hash;

public:
    typedef typename THTS<Domain>::Node Node;
    

    THTS_RT(Domain& domain, string algorithm, int lookahead) : THTS<Domain>(domain, algorithm), lookahead(lookahead){
    }

    struct compare_fval {
        bool operator()(const shared_ptr< Node> lhs, const shared_ptr< Node> rhs){
            // return lhs->g + lhs->h  > rhs->g + rhs->h;
            return lhs->fval > rhs->fval;
        }
    };

    ResultContainer getPlan(){
        cout << THTS <Domain>::algorithm << endl;
        // While time allows and no plan found do
        // TODO in my case, it will be the max look ahead
        int t = 0;
        while (t < THTS <Domain>::max_time && THTS <Domain>::goal_found == false){ cout << 21 << endl;

            if (THTS <Domain>::domain.isGoal(THTS <Domain>::root->state)){
                cout << "RT GOAL!" << endl;
                break;
            }

            int expansions = THTS <Domain>::res.nodesExpanded;

            // Expansion phase
            while(THTS <Domain>::res.nodesExpanded - expansions < lookahead){
                THTS <Domain>::performTrial();
                cout << THTS <Domain>::res.nodesExpanded << " " << lookahead << endl;
                if (THTS<Domain>::goal_found){
                    THTS<Domain>::goal_found = false;
                    cout << 32 << endl;
                    break;
                }
            }

            // TODO RTA* style, update state to the second best heuristic + edgecost
            // Change current state h to the sencond best, RTA* style
            // priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, compare_fval> PQueue;
            // for (shared_ptr<Node> child : THTS<Domain>::root->successors){
            //     PQueue.push(child);
            // }
            // if (!PQueue.empty()){
            //     PQueue.pop();
            //     if (!PQueue.empty()){
            //         // More than one successors
            //         cout << "B" <<  THTS<Domain>::domain.heuristic(THTS<Domain>::root->state) << endl;
            //         THTS<Domain>::domain.updateHeuristic(THTS<Domain>::root->state, PQueue.top()->fval + 1);
            //         cout << THTS<Domain>::domain.heuristic(THTS<Domain>::root->state) << endl;

            //     } else {
            //         THTS<Domain>::domain.updateHeuristic(THTS<Domain>::root->state, THTS<Domain>::root->fval + 1);
            //     }
            // }
            
            // Action selection phase
            cout << endl;
            cout << THTS<Domain>::root->state << endl;
            THTS <Domain>::selectAction(THTS <Domain>::root);
            THTS <Domain>::root->parent = nullptr;
            // THTS <Domain>::root->successors.clear();
            // THTS <Domain>::root->initialized = false;



            cout << THTS<Domain>::root->state << endl;
            cout << "G:" << THTS<Domain>::root->g << endl;
            cout << endl;

            cout << THTS<Domain>::root->state.getLabel() << endl;
            

            ++t;
            THTS <Domain>::TT.clear();
        }

        return THTS <Domain>::res;
    }

protected:
    double solCost = 0;
    int lookahead;
};