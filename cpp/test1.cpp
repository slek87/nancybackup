#include <iostream>
#include <string>
#include <fstream>
#include "RealTimeSearch.h"
#include "decisionAlgorithms/KBestBackup.h"
#include "expansionAlgorithms/AStar.h"
#include "expansionAlgorithms/BreadthFirst.h"
#include "expansionAlgorithms/DepthFirst.h"
#include "expansionAlgorithms/Risk.h"
#include "learningAlgorithms/Ignorance.h"
#include "learningAlgorithms/Dijkstra.h"
#include "domain/TreeWorld.h"
#include "domain/SlidingTilePuzzle.h"
#include "domain/PancakePuzzle.h"
#include "domain/HeavyTilePuzzle.h"
#include "sai/trialbased_rt.h"


using namespace std;

int main(int argc, char** argv)
{
	if ( argc < 3){
		cout << "Wrong number of argument" << endl;
		exit(1);
	}

	string domain = argv[1];
	int lookaheadDepth = stoi(argv[2]);

	ResultContainer fhatRes;
	ResultContainer riskRes;
	ResultContainer lsslrtabestfRes;
	ResultContainer lsslrtakbestRes;
	ResultContainer wasRes;
	ResultContainer guctsRes;



	if (domain == "Pancake" || domain == "PancakeDPS" ){
		PancakePuzzle world = PancakePuzzle(cin);
		if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
		RealTimeSearch<PancakePuzzle> fhat(world, "f-hat", "learn", "k-best", lookaheadDepth, 1, "normal");
		RealTimeSearch<PancakePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");
		RealTimeSearch<PancakePuzzle> lsslrtabestf(world, "a-star", "learn", ",minimin", lookaheadDepth);
		RealTimeSearch<PancakePuzzle> lsslrtakbest(world, "a-star", "learn", ",minimin", lookaheadDepth);
        THTS_RT <PancakePuzzle> thtswa(world, "WAS", lookaheadDepth);
        THTS_RT <PancakePuzzle> thtsgucts(world, "GUCTS", lookaheadDepth);

		fhatRes = fhat.search();
		riskRes = risk.search();
		lsslrtabestfRes = lsslrtabestf.search();
		lsslrtakbestRes = lsslrtakbest.search();
        wasRes = thtswa.getPlan();
        guctsRes = thtsgucts.getPlan();

	} else if (domain == "TreeWorld"){
		TreeWorld world = TreeWorld(cin);

		RealTimeSearch<TreeWorld> fhat(world, "f-hat", "none", "k-best", lookaheadDepth, 1, "normal");
		RealTimeSearch<TreeWorld> risk(world, "risk", "none", "k-best", lookaheadDepth, 1, "normal");

	} else if (domain == "SlidingPuzzle")	{
		SlidingTilePuzzle world = SlidingTilePuzzle(cin);

		RealTimeSearch<SlidingTilePuzzle> fhat(world, "f-hat", "learn", "k-best", lookaheadDepth, 1, "normal");
		RealTimeSearch<SlidingTilePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");

		riskRes = risk.search();
		fhatRes = fhat.search();
	} else if (domain == "HeavyTile")	{
		HeavyTilePuzzle world = HeavyTilePuzzle(cin);

		RealTimeSearch<HeavyTilePuzzle> fhat(world, "f-hat", "learn", "k-best", lookaheadDepth, 1, "normal");
		RealTimeSearch<HeavyTilePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");

		riskRes = risk.search();
		fhatRes = fhat.search();
	} else {
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	string result = ";"
	if (argc < 4){
		cout << result << endl;
	} else {
		ofstream out(argv[3]);
		out << result;
		out.close();
	}

}
