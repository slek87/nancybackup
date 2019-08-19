#include <iostream>
#include <string>
#include <fstream>
#include "RealTimeSearch.h"
#include "decisionAlgorithms/ScalarBackup.h"
#include "expansionAlgorithms/AStar.h"
#include "learningAlgorithms/Dijkstra.h"
#include "domain/TreeWorld.h"
#include "domain/SlidingTilePuzzle.h"
#include "domain/PancakePuzzle.h"
#include "domain/HeavyTilePuzzle.h"
#include "domain/InverseTilePuzzle.h"

using namespace std;

int main(int argc, char** argv){
	if ( argc < 3){
		cout << "Wrong number of arguments: [executable] [domain] [expansion limit] [optional: output file] < [domain file]" << endl;
		exit(1);
	}
	// Get the lookahead depth
	int lookaheadDepth = stoi(argv[2]);
    bool check = false;
	// Get the domain type
	string domain = argv[1];

	ResultContainer res;

	if (domain == "Pancake" || domain == "PancakeDPS" ){
		PancakePuzzle world = PancakePuzzle(cin);
		if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
		RealTimeSearch<PancakePuzzle> iep(world, "iep", "learn", "iep", lookaheadDepth);
		res = iep.search();
		if (check && !world.validatePath(res.path)) exit(1);

	} else if (domain == "TreeWorld"){
		TreeWorld world = TreeWorld(cin);
		RealTimeSearch<TreeWorld> iep(world, "iep", "none", "iep", lookaheadDepth);
		res = iep.search();

	} else if (domain == "SlidingPuzzle") {
		SlidingTilePuzzle world = SlidingTilePuzzle(cin);
		RealTimeSearch<SlidingTilePuzzle> iep(world, "iep", "learn", "iep", lookaheadDepth);
		res = iep.search();
		if (check && !world.validatePath(res.path)) exit(1);

	} else if (domain == "HeavyTile") {
		HeavyTilePuzzle world = HeavyTilePuzzle(cin);
		RealTimeSearch<HeavyTilePuzzle> iep(world, "iep", "learn", "iep", lookaheadDepth);
		res = iep.search();
		if (check && !world.validatePath(res.path)) exit(1);

	} else if (domain == "InverseTile") {
		InverseTilePuzzle world = InverseTilePuzzle(cin);
		RealTimeSearch<InverseTilePuzzle> iep(world, "iep", "learn", "iep", lookaheadDepth);
		res = iep.search();
		if (check && !world.validatePath(res.path)) exit(1);
		
	} else {
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	string result = "IEP-P," + domain + "," + to_string(res.solutionCost) + "," + to_string(res.nodesGenerated) + "," + to_string(res.nodesExpanded) + "," + to_string(lookaheadDepth);

	if (argc < 4)	{
		cout << result << endl;
	} else {
		ofstream out(argv[3]);
		out << result;
		out.close();
	}
}
