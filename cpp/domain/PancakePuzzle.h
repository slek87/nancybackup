#pragma once
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include "../utility/SlidingWindow.h"

#include <bitset>

using namespace std;

class PancakePuzzle {
public:
    typedef double Cost;
	static constexpr Cost COST_MAX = std::numeric_limits<Cost>::max();

    class State {
	public:
		State() {}

		State(std::vector<int> b, int l) : ordering(b), label(l) {}

		std::vector<int> getOrdering() const {
			return ordering;
		}

		friend std::ostream& operator<<(std::ostream& stream, const PancakePuzzle::State& state) {
			for (int r = 0; r < state.getOrdering().size(); r++)
			{
				stream << endl;
			}
			return stream;
		}

		std::string toString() const {
			std::string s = "";
			for (int r = 0; r < ordering.size(); r++)
			{
				s += "\n";
			}
			return s;
		}

		int getLabel() const
			{
				return label;
			}

		void markStart()
		{
			label = 's';
		}

    private:
		std::vector<int> ordering;
		int label;
		unsigned long long theKey = -1;
	};

struct HashState
	{
		std::size_t operator()(const State &s) const
		{   
            // TODO
			return 1;
		}
	};


    PancakePuzzle(int size, int variant, int seed ) {
        // Variants:
        // 0: Regular pancake puzzle, where each flip cost 1.
        // 1: Cost is max of two elements of each end of the set being flipped.
        // 2: Each pancake has a weight, equal to its index. 
        //    The cost is the sum of the indexes of pancakes being flipped.


        srand(seed);

        for (int i = 0; i < size; ++i){
            startOrdering.push_back(rand() % size + 1);
        }

        endOrdering = startOrdering;
        sort(endOrdering.begin(), endOrdering.end()); 
    
        puzzleVariant = variant;
    }

    bool isGoal(const State& s) const {
		if (s.getOrdering() == endOrdering)
		{
			return true;
		}

		return false;
	}

    Cost distance(const State& state) {
		// Check if the distance of this state has been updated
		if (correctedD.find(state) != correctedD.end())
		{
			return correctedD[state];
		}

        // TODO
		Cost d = 1;
		// updateDistance(state, d);

		return correctedD[state];
	}

    Cost distanceErr(const State& state) {
		// Check if the distance error of this state has been updated
		if (correctedDerr.find(state) != correctedDerr.end())
		{
			return correctedDerr[state];
		}

		// TODO
		Cost d = 1;
		// updateDistance(state, d);

		return correctedD[state];
	}

    Cost heuristic(const State& state) {
		// Check if the heuristic of this state has been updated
		if (correctedH.find(state) != correctedH.end())
		{
			return correctedH[state];
		}

		Cost h = 1; //manhattanDistance(state);
		//updateHeuristic(state, h);

		return correctedH[state];
	}

    Cost epsilonHGlobal()	{
		return curEpsilonH;
	}

	Cost epsilonDGlobal()	{
		return curEpsilonD;
	}

    void updateEpsilons()	{
		if (expansionCounter == 0)
		{
			curEpsilonD = 0;
			curEpsilonH = 0;

			return;
		}

		curEpsilonD = epsilonDSum / expansionCounter;

		curEpsilonH = epsilonHSum / expansionCounter;
	}

    void pushEpsilonHGlobal(double eps)	{
		if (eps < 0)
			eps = 0;
		else if (eps > 1)
			eps = 1; // TODO: TreeWorld have eps = maxEdgeCost. Why?

		epsilonHSum += eps;
		expansionCounter++;
	}

    void updateDistance(const State& state, Cost value) {
		correctedD[state] = value;
	}

	void updateDistanceErr(const State& state, Cost value) {
		correctedDerr[state] = value;
	}

	void updateHeuristic(const State& state, Cost value) {
		correctedH[state] = value;
	}

    double getBranchingFactor() const	{
		return size - 1; // TODO I think this is right
	}

    void flipOrdering(std::vector<State>& succs, std::vector<int> ordering, int loc) const {
		int start = 0;
		int end = loc;
		while(start < loc){
			std::swap(ordering[start++], ordering[end--]);
		}
		succs.push_back(State(ordering, loc));
        
    }

    std::vector<State> successors(const State& state) const {
		std::vector<State> successors;

        // TODO return all the different states based on flipping at i
        for (int i = size - 1; i > 0; --i){
			flipOrdering(successors, state.getOrdering(), i);
        }
		return successors;
	}

    std::vector<State> predecessors(const State& state) const {
		std::vector<State> predecessors;

		// TODO return all the different states based on flipping at i
        for (int i = size - 1; i > 0; --i){
			flipOrdering(predecessors, state.getOrdering(), i);
        }
		return predecessors;
	}

	bool safetyPredicate(const State& state) const { return true; }

	const State getStartState() const {
		return startState;
	}

	Cost getEdgeCost(State state) {
		// TODO
		return 1;
	}

	string getDomainInformation()
	{
		string variant;
		if (puzzleVariant == 0){
			variant = "\"Pancake Puzzle\"";
		} else if (puzzleVariant == 1){
			variant = "\"Heavy Pancake Puzzle1\"";
		} else if (puzzleVariant == 2){
			variant = "\"Heavy Pancake Puzzle2\"";
		}
		string info = "{ \"Domain\": " + variant + ", \"Dimensions\": " + 
			std::to_string(size) + " }";
		return info;
	}

    string getDomainName()	{
		if (puzzleVariant == 0)
            return "PancakePuzzle";
        
        // Cost is max of two elements of each end of the set being flipped
        if (puzzleVariant == 1)
            return "HeavyPancakePuzzle1";

        // Cost of starting index
        if (puzzleVariant == 2)
            return "HeavyPancakePuzzle2";
	}

	void initialize(string policy, int la)	{
		epsilonDSum = 0;
		epsilonHSum = 0;
		expansionCounter = 0;
		curEpsilonD = 0;
		curEpsilonH = 0;

		expansionPolicy = policy;
		lookahead = la;
		correctedD.clear();
		correctedDerr.clear();
		correctedH.clear();
		expansionDelayWindow.clear();
	}

    void pushDelayWindow(int val)	{
		expansionDelayWindow.push(val);
	}

	double averageDelayWindow()	{
		if (expansionDelayWindow.size() == 0)
			return 1;

		double avg = 0;

		for (auto i : expansionDelayWindow)
		{
			avg += i;
		}

		avg /= expansionDelayWindow.size();

		return avg;
	}

    std::vector<int> startOrdering;
	std::vector<int> endOrdering;
    
    State startState;
	SlidingWindow<int> expansionDelayWindow;
	unordered_map<State, Cost, HashState> correctedH;
	unordered_map<State, Cost, HashState> correctedD;
	unordered_map<State, Cost, HashState> correctedDerr;
    int puzzleVariant;
    int size;

    double epsilonHSum;
	double epsilonDSum;
	double curEpsilonH;
	double curEpsilonD;
	double expansionCounter;

    string expansionPolicy;
	int lookahead;

};

