#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"

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

	double sample(State s, int max_depth){
		State cur = s;
		int depth = 0;
		double cost = 0;

		while(!domain.isGoal(cur) && depth < max_depth){
			vector<State> children = domain.successors(cur);
			int r = randNum(children.size());
			cur = children[r];
			double c = domain.getEdgeCost(cur);
			cost += c;
			++depth;
		} 
	
		return cost;
	}

	double randomSampling(){
		domain.initialize("randomSampling", lookahead);
		State cur = domain.getStartState();

		// Might get tricky with tile world, will have to revisit
		int branches = domain.getBranchingFactor();
		int expansion_credit = lookahead / branches - 1;
		int max_depth = pow(lookahead - branches, 1.0/branches) / 2;
		int probe_per_child = expansion_credit / max_depth;

		double totalcost = 0;


		while (!domain.isGoal(cur)){
			// Get tla
			vector<State> children = domain.successors(cur);
			double tla_sample_cost[branches];

			for (int c = 0; c < branches; ++c){

				double best_cost = numeric_limits<double>::infinity();
				for (int p = 0; p < probe_per_child; ++p){
					double sample_cost = sample(children[c], max_depth); ;
					sample_cost += domain.getEdgeCost(children[c]);

					if (sample_cost < best_cost){
						best_cost = sample_cost;
					}
				}
				tla_sample_cost[c] = best_cost;
			}

			// pick the best tla
			int index = 0;

			for(int i = 1; i < branches; ++i)
			{
				if(tla_sample_cost[i] < tla_sample_cost[index])
					index = i;              
			}

			cur = children[index];
			totalcost += domain.getEdgeCost(cur);
		}
		return totalcost;
	}

	/*
	double sample(State s, int max_depth){
		State cur = s;
		int depth = 0;
		double cost = 0;

		while(!domain.isGoal(cur) && depth < max_depth){
			vector<State> children = domain.successors(cur);
			int r = randNum(children.size());
			cur = children[r];
			double c = domain.getEdgeCost(cur);
			cout << "[" << c << "] ";
			cost += c;
			++depth;
		} 
		cout << endl;
		return cost;
	}

	double sampling(){
		domain.initialize("randomSampling", lookahead);
		State cur = domain.getStartState();

		// Might get tricky with tile world, will have to revisit
		int branches = domain.getBranchingFactor();
		int expansion_credit = lookahead / branches - 1;
		int max_depth = pow(lookahead - branches, 1.0/branches);
		int probe_per_child = expansion_credit / max_depth;

		double totalcost = 0;

		cout << "bra:" << branches << " exp/child:" << expansion_credit << " max d:" << max_depth << " ppc:" << probe_per_child << endl;

		while (!domain.isGoal(cur)){
			// Get tla
			vector<State> children = domain.successors(cur);
			double tla_sample_cost[branches];

			for (int c = 0; c < branches; ++c){
				cout << endl;

				double best_cost = numeric_limits<double>::infinity();
				for (int p = 0; p < probe_per_child; ++p){
					cout << "CHILD:" << c << "\ncost to:" << domain.getEdgeCost(children[c]) << endl;
					double sample_cost = sample(children[c], max_depth); ;
					cout << "sample cost:" << sample_cost << endl;

					sample_cost += domain.getEdgeCost(children[c]);

					cout << "total: " << sample_cost << endl;
					if (sample_cost < best_cost){
						best_cost = sample_cost;
					}
				}
				tla_sample_cost[c] = best_cost;
				cout << "BEST:" << best_cost << endl;
			}

			// pick the best tla
			int index = 0;

			for(int i = 1; i < branches; ++i)
			{
				if(tla_sample_cost[i] < tla_sample_cost[index])
					index = i;              
			}

			cur = children[index];
			totalcost += domain.getEdgeCost(cur);
			cout << "\nBEST CHILD:" << index << " path cost:" << totalcost << endl;
		}

		return totalcost;
	}
	*/

	/*
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
	*/
private:
	static int randNum(int max){
		int x = rand() % max;
		return x;
	}

protected:
	Domain& domain;
	double lookahead;
};