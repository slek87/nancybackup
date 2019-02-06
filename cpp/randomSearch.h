#include "domain/TreeWorld.h"
#include "domain/SlidingTilePuzzle.h"

using namespace std;

template <class Domain>
class RandomSearch
{
public:
	typedef typename Domain::State State;
	typedef typename Domain::Cost Cost;

	RandomSearch(Domain& domain, double lookahead)
	:domain(domain), lookahead(lookahead){
		srand(time(0));
	}

	double randomSearch(){
		domain.initialize("randomSearch", lookahead);
		State cur = domain.getStartState();
		int r;
		double cost = 0;

		while (!domain.isGoal(cur)){
			vector<State> children = domain.successors(cur);
			r = randNum(children.size());
			cur = children[r];
			cost += domain.getEdgeCost(cur);
		}
		return cost;
	}

	double randomSampling(int ksamples){
		domain.initialize("randomSampling", lookahead);
		State cur = domain.getStartState();

		int bestChild = -1;
		double bestCost = numeric_limits<double>::infinity();
		double totalcost = 0;
		
		while (!domain.isGoal(cur)){

			vector<State> children = domain.successors(cur);
			for (int c = 0; c < children.size(); ++c){
				double cost = 0;
				for (int i = 0; i < ksamples; ++i){
					cost += sampleChild(children[c], lookahead - 1);
				} 
				cost = cost / ksamples;
				// cout << "sampling child " << c << " avg cost: " << cost << endl;
				
				if (cost < bestCost){
					bestChild = c;
					bestCost = cost;
				}

				
			}
			
			// cout << "picking child " << bestChild << "\n" << endl;
			cur = children[bestChild];
			totalcost += domain.getEdgeCost(cur);
		}
		

		return totalcost;
	}

	double sampleChild(State s, int maxdepth){
		State cur = s;
		double cost = 0;
		int start_depth = s.getDepth();
		int depth = 0;
		while(!domain.isGoal(cur) && depth < maxdepth){
			vector<State> children = domain.successors(cur);
			int r = randNum(children.size());
			cur = children[r];
			double c = domain.getEdgeCost(cur);
			cost += c;
			// cout << c << " ";
			++depth;
		} 
		// cout << endl;
		return cost;
	}

private:
	static int randNum(int max){
		int x = rand() % max;
		return x;
	}

protected:
	Domain& domain;
	double lookahead;
};