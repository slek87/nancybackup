#include <iostream>
#include <string>
#include <fstream>
#include "RealTimeSearch.h"
#include "decisionAlgorithms/KBestBackup.h"
#include "expansionAlgorithms/Risk.h"
#include "learningAlgorithms/Dijkstra.h"
#include "domain/TreeWorld.h"
#include "domain/SlidingTilePuzzle.h"
#include "domain/PancakePuzzle.h"
#include "domain/HeavyTilePuzzle.h"

using namespace std;

int main(int argc, char** argv){
	if ( argc < 3){
		cout << "Wrong number of arguments: ./expansionTests.sh <Domain Type> <expansion limit> <optional: output file> < <domain file>" << endl;
		exit(1);
	}

	// Get the lookahead depth
	int lookaheadDepth = stoi(argv[2]);

	// Get the domain type
	string domain = argv[1];

	ResultContainer optimisticRes;
	ResultContainer riskRes;

	if (domain == "Pancake" || domain == "PancakeDPS" ){
		// PancakePuzzle world = PancakePuzzle(16, 0, time(NULL));
		PancakePuzzle world = PancakePuzzle(cin);
		if (domain == "PancakeDPS"){
			world.setVariant(1);
		}

		// RealTimeSearch<PancakePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth);
		// riskRes = risk.search();

		// RealTimeSearch<PancakePuzzle> optimistic(world, "risk", "learn", "optimistic", lookaheadDepth);
		// optimisticRes = optimistic.search();

		RealTimeSearch<PancakePuzzle> ie(world, "ie", "learn", "ie", lookaheadDepth);
		optimisticRes = ie.search();

	} else if (domain == "TreeWorld"){
		// Make a tree world
		TreeWorld world = TreeWorld(cin);
		RealTimeSearch<TreeWorld> risk(world, "risk", "none", "k-best", lookaheadDepth);
		riskRes = risk.search();

		RealTimeSearch<TreeWorld> optimistic(world, "risk", "learn", "optimistic", lookaheadDepth);
		optimisticRes = optimistic.search();

	} else if (domain == "SlidingPuzzle") {
		// Make a tile puzzle
		SlidingTilePuzzle world = SlidingTilePuzzle(cin);
		// RealTimeSearch<SlidingTilePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth);
		// riskRes = risk.search();

		// RealTimeSearch<SlidingTilePuzzle> optimistic(world, "risk", "learn", "optimistic", lookaheadDepth);
		// optimisticRes = optimistic.search();

		RealTimeSearch<SlidingTilePuzzle> ie(world, "ie", "learn", "ie", lookaheadDepth);
		optimisticRes = ie.search();


	} else if (domain == "HeavyTile") {

		HeavyTilePuzzle world = HeavyTilePuzzle(cin);
		RealTimeSearch<HeavyTilePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth);
		riskRes = risk.search();

		RealTimeSearch<HeavyTilePuzzle> optimistic(world, "risk", "learn", "optimistic", lookaheadDepth);
		optimisticRes = optimistic.search();

	} else {
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	// string result = "{ \"BFS\": " + to_string(bfsRes.solutionCost) + 
	string result = "{ \"Optimistic\": " +	to_string(optimisticRes.solutionCost) + 
		", \"Risk\": " + to_string(riskRes.solutionCost) + " }";

	if (argc < 4)	{
		cout << result << endl;
	} else {
		ofstream out(argv[3]);
		out << result;
		out.close();
	}
}
