#pragma once
#include <functional>
#include <limits>
#include "DecisionAlgorithm.h"
#include "../utility/PriorityQueue.h"
#include <math.h>

using namespace std;

template <class Domain, class Node, class TopLevelAction>
class OptimisticBackup : public DecisionAlgorithm<Domain, Node, TopLevelAction>
{
	typedef typename Domain::State State;
	typedef typename Domain::Cost Cost;

public:
	OptimisticBackup(){}

	Node* backup(PriorityQueue<Node*>& open, vector<TopLevelAction>& tlas, Node* start)	{
        double mostOptimistic = numeric_limits<double>::infinity();
        Node* goalPrime;

        for (TopLevelAction& tla : tlas){
            Node* best = tla.open.top();

            double mean =  best->getFHatValue();

            if (mean < mostOptimistic){
                mostOptimistic = mean;
                goalPrime = best;
            }
            
            // while (!tla.open.empty()){
            //     Node* best = tla.open.top();
			// 	tla.open.pop();

            //     double f = best->getFValue();
            //     double mean =  best->getFHatValue();
            //     double d = best->getDValue();
            //     double error = best->getFHatValue() - best->getFValue();

            //     // if (d == 0){
            //     //     // This is the goal
            //     //     return best;
            //     // }

            //     double lower = f;
            //     if (f != mean){
            //         double stdDev = error / 2.0;
            //         double var = pow(stdDev, 2);
            //         // Lower limit of CI
            //         lower = max(f, mean - (1.96 * var));
            //     }

            //     if (lower < mostOptimistic){
            //         mostOptimistic = lower;
            //         goalPrime = best;
            //     }
            // }
        }

        return goalPrime;
	}
private:
protected:
};