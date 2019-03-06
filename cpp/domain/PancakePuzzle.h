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

		State(std::vector<int> b, int l) : ordering(b), label(l) {
			generateKey();
		}

		std::vector<int> getOrdering() const {
			return ordering;
		}

		friend std::ostream& operator<<(std::ostream& stream, const PancakePuzzle::State& state) {
			for (int r = 0; r < state.getOrdering().size(); r++)
			{
				stream << std::setw(3) << state.getOrdering()[r] << " ";
			}
			stream << endl;
			return stream;
		}

		bool operator==(const State& state) const {
			return ordering == state.getOrdering();
		}


		bool operator!=(const State& state) const {
			return ordering != state.getOrdering();
		}

		void generateKey() {
			// This will provide a unique hash for every state in the 15 puzzle,
			// Other puzzle variants may/will see collisions...
			vector<unsigned char> v;
			for (int u : ordering){
				v.push_back(u);
			}
			theKey = std::hash<std::string>() ( std::string( v.begin(), v.end() ) ) ;
		}

		unsigned long long key() const {
			return theKey;
		}

		std::string toString() const {
			std::string s = "";
			for (int r = 0; r < ordering.size(); r++)
			{
				s += std::to_string(ordering[r]) + " ";
			}
			return s + "\n";
		}

		int getLabel() const
			{
				return label;
			}

		void markStart()
		{
			label = 0;
		}

    private:
		std::vector<int> ordering;
		int label;
		unsigned long long theKey = -1;

	};
	
	struct HashState
	{
		// I think that this will work for puzzles up to size 255
		// Because it will convert each int to a char, which is 8 bytes
		// So the biggest number 255

		/*
		std::size_t operator()(const State &s) const
		{   
			vector<unsigned char> v;
			for (int u : s.getOrdering()){
				v.push_back(u);
			}
			return std::hash<std::string>() ( std::string( v.begin(), v.end() ) ) ;
		}
		*/

		std::size_t operator()(const State &s) const{

			return s.key();
		}

	};

	PancakePuzzle(std::istream& input) {
		// Get the size of pancake
		string line;
		getline(input, line);
		stringstream ss(line);
		ss >> size;

		if (size > 255){
			fprintf (stderr, "Max pancake size is 255\n");
			exit(1);
		}
		// Skip the next line
		getline(input, line);
		std::vector<int> rows(size, 0);

		startOrdering = rows;
		endOrdering = rows;

		for (int i = 0; i < size; ++i){
			getline(input, line);
			startOrdering[i] = stoi(line);			
		}
		// Skip the next line
		getline(input, line);

		for (int i = 0; i < size; ++i){
			getline(input, line);
			endOrdering[i] = stoi(line);			
		}

		puzzleVariant = 0; // Default
		startState = State(startOrdering, 0);

	}

	
    PancakePuzzle(int len, int variant, int seed ) {
        // Variants:
        // 0: Regular pancake puzzle, where each flip cost 1.
        // 1: Cost is max of two elements of each end of the set being flipped.
        // 2: Each pancake has a weight, equal to its index. 
        //    The cost is the sum of the indexes of pancakes being flipped.

		if (len > 255){
			fprintf (stderr, "Max pancake size is 255\n");
			exit(1);
		}

        srand(seed);

		std::unordered_map<int, char> numbers;
	
		// Generating random unique numbers
		while (startOrdering.size() < len){
			int tmp = numbers.size();
			int rr = rand() % len + 1;
			numbers[rr] = 0;
			if (tmp != numbers.size()){
				startOrdering.push_back(rr);
			}
		}

        endOrdering = startOrdering;
        sort(endOrdering.begin(), endOrdering.end()); 
    
        puzzleVariant = variant;
		size = len;

		startState = State(startOrdering, 0);
    }

	void setVariant(int variant){
		puzzleVariant = variant;
	}

    bool isGoal(const State& s) const {
		if (s.getOrdering() == endOrdering)
		{
			return true;
		}

		return false;
	}

	Cost gapHeuristic(const State& state) const {
		// Using gap heuristic from - Landmark Heuristics for the Pancake Problem
		int size = state.getOrdering().size();
		int plate = size + 1;
		int sum = 0;

		for (int i = 1; i < size; ++i ){

			int dif = state.getOrdering()[i - 1] - state.getOrdering()[i]; 
			if (dif > 1 || dif < -1)
				++sum;
		}

		int dif = state.getOrdering()[size - 1] - plate;
		if (dif > 1 || dif < -1)
			++sum;
		
		return sum;
	}

    Cost distance(const State& state) {
		// Check if the distance of this state has been updated
		if (correctedD.find(state) != correctedD.end())
		{
			return correctedD[state];
		}

		Cost d = gapHeuristic(state);
		updateDistance(state, d);

		return correctedD[state];
	}

    Cost distanceErr(const State& state) {
		// Check if the distance error of this state has been updated
		if (correctedDerr.find(state) != correctedDerr.end())
		{
			return correctedDerr[state];
		}

		Cost derr = gapHeuristic(state);
		updateDistanceErr(state, derr);

		return correctedDerr[state];
	}

    Cost heuristic(const State& state) {
		// Check if the heuristic of this state has been updated
		if (correctedH.find(state) != correctedH.end())
		{
			return correctedH[state];
		}

		Cost h = gapHeuristic(state);
		updateHeuristic(state, h);

		return correctedH[state];
	}

    Cost epsilonHGlobal()	{
		return curEpsilonH;
	}

	Cost epsilonDGlobal()	{
		return curEpsilonD;
	}

    void updateEpsilons()	{
		// TODO

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
		// TODO

		if (eps < 0)
			eps = 0;
		/* No idea why set the limit to 1
		else if (eps > 1){
			eps = 1;
		}
		*/
		epsilonHSum += eps;
		expansionCounter++;
	}

	void pushEpsilonDGlobal(double eps) {
		// TODO

		if (eps < 0)
			eps = 0;
		/*
		else if (eps > 1)
			eps = 1;
		*/
		epsilonDSum += eps;
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
		// TODO
		return size - 1; //  I think this is right
	}

    void flipOrdering(std::vector<State>& succs, std::vector<int> ordering, int loc) const {
		int start = 0;
		int end = loc;
		while(start < end){
			std::swap(ordering[start++], ordering[end--]);
		}
		succs.push_back(State(ordering, loc));
        
    }

    std::vector<State> successors(const State& state) const {
		std::vector<State> successors;
        for (int i = size - 1; i > 0; --i){
			flipOrdering(successors, state.getOrdering(), i);
        }
		return successors;
	}

    std::vector<State> predecessors(const State& state) const {
		std::vector<State> predecessors;
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
		// Looking at Andew's code, it looks like this is called
		// mostly on successors being generated. So the label
		// will tell which index the parent chose to flip at.

		// Variants:
        // 0: Regular pancake puzzle, where each flip cost 1.
        // 1: Cost is max of two elements of each end of the set being flipped.
        // 2: Each pancake has a weight, equal to its index. 
        //    The cost is the sum of the indexes of pancakes being flipped.

	
		int l = state.getLabel();

		if (puzzleVariant == 1){
			int i = state.getOrdering()[0];
			int j = state.getOrdering()[l];
			if ( i > j)
				return i;
			return j; 
		}

		if (puzzleVariant == 2){
			int sum = 0;
			for (int i = 1; i <= l; ++i) {
				sum += i;
			}
			return sum;
		}

		// Variant 1 
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

		return "Unknow variant";
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
