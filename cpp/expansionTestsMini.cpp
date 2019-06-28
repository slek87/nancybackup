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

using namespace std;

bool DEBUG = true;

int main(int argc, char** argv)
{
	if ( argc < 3)
	{
		cout << "Wrong number of arguments: ./expansionTests.sh <Domain Type> <expansion limit> <optional: output file> < <domain file>" << endl;
		cout << "Available domains are Pancake, PancakeDPS, TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	// Get the lookahead depth
	int lookaheadDepth = stoi(argv[2]);

	// Get the domain type
	string domain = argv[1];
	string lsslrta_backup = "minimin";

	ResultContainer bfsRes;
	ResultContainer astarRes;
	ResultContainer fhatRes;
	ResultContainer riskRes;
	ResultContainer lsslrtaRes;

	if (domain == "Pancake" || domain == "PancakeDPS" ){
		// PancakePuzzle world = PancakePuzzle(16, 0, time(NULL));
		PancakePuzzle world = PancakePuzzle(cin);
		if (domain == "PancakeDPS"){
		
			world.setVariant(1);
		}


		RealTimeSearch<PancakePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");

		riskRes = risk.search();



	} else if (domain == "TreeWorld")
	{
		// Make a tree world
		TreeWorld world = TreeWorld(cin);

		RealTimeSearch<TreeWorld> risk(world, "risk", "none", "k-best", lookaheadDepth, 1, "normal");

		riskRes = risk.search();
	}
	else if (domain == "SlidingPuzzle")
	{
		// Make a tile puzzle
		SlidingTilePuzzle world = SlidingTilePuzzle(cin);

		RealTimeSearch<SlidingTilePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");

		riskRes = risk.search();
	}
	else
	{
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	// string result = "{ \"BFS\": " + to_string(bfsRes.solutionCost) + 
	string result = "{ \"A*\": " +	to_string(astarRes.solutionCost) + 
		", \"F-Hat\": " + to_string(fhatRes.solutionCost) +
		", \"Risk\": " + to_string(riskRes.solutionCost) + 
		", \"LSS-LRTA*\": " + to_string(lsslrtaRes.solutionCost) +
		//", \"Random\": " + to_string(randomCost) +
		//", \"Random Sampling\": " + to_string(randomSamplingCost) +
		", \"Lookahead\": " + to_string(lookaheadDepth) + " }";

	if (argc < 4)
	{
		cout << result << endl;
	}
	else
	{
		ofstream out(argv[3]);

		out << result;
		out.close();
	}

}
