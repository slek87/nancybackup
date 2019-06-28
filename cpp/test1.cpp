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
#include <chrono> 

using namespace std;
using namespace std::chrono; 
auto t = high_resolution_clock::now(); 

void start(){
	t = high_resolution_clock::now(); 
}

void end(){
	auto now = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(now - t); 
	cout << "Time taken: " << duration.count() << " ms\n" << endl;
}

int main(int argc, char** argv)
{
	ResultContainer fhatRes;
	ResultContainer riskRes;
	ResultContainer lsslrtabestfRes;
	ResultContainer lsslrtakbestRes;
	ResultContainer wasRes;
	ResultContainer guctsfRes;
	ResultContainer guctsRes;

	if ( argc < 3){
		cout << "Wrong number of argument" << endl;
		exit(1);
	}

	string domain = argv[1];
	int lookaheadDepth = stoi(argv[2]);

	if (domain == "Pancake" || domain == "PancakeDPS" ){
		PancakePuzzle world = PancakePuzzle(cin);
		if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
		
		cout << "GUCTS-F" << endl;		        
		start();
		THTS_RT <PancakePuzzle> thtsguctsf(world, "GUCTS-F", lookaheadDepth);
        guctsfRes = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(guctsfRes.path)){
            cout << "Invalid path detected from GUCTS-F search!" << endl;
            exit(1);
        }
		

		cout << "GUCTS" << endl;
		start();
		THTS_RT <PancakePuzzle> thtsgucts(world, "GUCTS", lookaheadDepth);
		guctsRes = thtsgucts.getPlan();
		end();
		if (!world.validatePath(guctsRes.path)){
            cout << "Invalid path detected from GUCTS search!" << endl;
            exit(1);
        }

		cout << "WAS" << endl;
		start();
		THTS_RT <PancakePuzzle> thtswa(world, "WAS", lookaheadDepth);
        wasRes = thtswa.getPlan();
		end();
		if (!world.validatePath(wasRes.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }

		cout << "FHAT" << endl;
		start();
		RealTimeSearch<PancakePuzzle> fhat(world, "f-hat", "learn", "k-best", lookaheadDepth, 1, "normal");
		fhatRes = fhat.search();
		end();
		if (!world.validatePath(fhatRes.path)){
            cout << "Invalid path detected from FHAT search!" << endl;
            exit(1);
        }

		cout << "RISK" << endl;
		start();
		RealTimeSearch<PancakePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");
		riskRes = risk.search();
		end();
		if (!world.validatePath(riskRes.path)){
            cout << "Invalid path detected from RISK search!" << endl;
            exit(1);
        }

		cout << "LSS-LRTA BESTF" << endl;
		start();
		RealTimeSearch<PancakePuzzle> lsslrtabestf(world, "a-star", "learn", "minimin", lookaheadDepth);
		lsslrtabestfRes = lsslrtabestf.search();
		end();
		if (!world.validatePath(lsslrtabestfRes.path)){
            cout << "Invalid path detected from LSS-LRTA BESTF search!" << endl;
            exit(1);
        }

		cout << "LSS-LRTA KBEST" << endl;
		start();
		RealTimeSearch<PancakePuzzle> lsslrtakbest(world, "a-star", "learn", "k-best", lookaheadDepth);
		lsslrtakbestRes = lsslrtakbest.search();
		end();
		if (!world.validatePath(lsslrtakbestRes.path)){
            cout << "Invalid path detected from LSS-LRTA KBEST search!" << endl;
            exit(1);
        }

	} else if (domain == "TreeWorld"){
		TreeWorld world = TreeWorld(cin);

		cout << "GUCTS-F" << endl;		        
		start();
		THTS_RT <TreeWorld> thtsguctsf(world, "GUCTS-F", lookaheadDepth);
        guctsfRes = thtsguctsf.getPlan();
		end();
        
		cout << "GUCTS" << endl;
		start();
		THTS_RT <TreeWorld> thtsgucts(world, "GUCTS", lookaheadDepth);
		guctsRes = thtsgucts.getPlan();
		end();

		cout << "WAS" << endl;
		start();
		THTS_RT <TreeWorld> thtswa(world, "WAS", lookaheadDepth);
        wasRes = thtswa.getPlan();
		end();

		cout << "FHAT" << endl;
		start();
		RealTimeSearch<TreeWorld> fhat(world, "f-hat", "none", "k-best", lookaheadDepth, 1, "normal");
		fhatRes = fhat.search();
		end();

		cout << "RISK" << endl;
		start();
		RealTimeSearch<TreeWorld> risk(world, "risk", "none", "k-best", lookaheadDepth, 1, "normal");
		riskRes = risk.search();
		end();
		
		cout << "LSS-LRTA BESTF" << endl;
		start();
		RealTimeSearch<TreeWorld> lsslrtabestf(world, "a-star", "none", "minimin", lookaheadDepth);
		lsslrtabestfRes = lsslrtabestf.search();
		end();
		
		cout << "LSS-LRTA KBEST" << endl;
		start();
		RealTimeSearch<TreeWorld> lsslrtakbest(world, "a-star", "none", "k-best", lookaheadDepth);
		lsslrtakbestRes = lsslrtakbest.search();
		end();
        
	} else if (domain == "SlidingPuzzle")	{
		SlidingTilePuzzle world = SlidingTilePuzzle(cin);
		
		cout << "GUCTS-F" << endl;
		start();
		THTS_RT <SlidingTilePuzzle> thtsguctsf(world, "GUCTS-F", lookaheadDepth);
        guctsfRes = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(guctsfRes.path)){
            cout << "Invalid path detected from GUCTS-F search!" << endl;
            exit(1);
        }
        
		cout << "GUCTS" << endl;
		start();
		THTS_RT <SlidingTilePuzzle> thtsgucts(world, "GUCTS", lookaheadDepth);
		guctsRes = thtsgucts.getPlan();
		end();
		if (!world.validatePath(guctsRes.path)){
            cout << "Invalid path detected from GUCTS search!" << endl;
            exit(1);
        }

		cout << "WAS" << endl;
		start();
		THTS_RT <SlidingTilePuzzle> thtswa(world, "WAS", lookaheadDepth);
        wasRes = thtswa.getPlan();
		end();
		if (!world.validatePath(wasRes.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }

		cout << "FHAT" << endl;
		start();
		RealTimeSearch<SlidingTilePuzzle> fhat(world, "f-hat", "learn", "k-best", lookaheadDepth, 1, "normal");
		fhatRes = fhat.search();
		end();
		if (!world.validatePath(fhatRes.path)){
            cout << "Invalid path detected from FHAT search!" << endl;
            exit(1);
        }

		cout << "RISK" << endl;
		start();
		RealTimeSearch<SlidingTilePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");
		riskRes = risk.search();
		end();
		if (!world.validatePath(riskRes.path)){
            cout << "Invalid path detected from RISK search!" << endl;
            exit(1);
        }

		cout << "LSS-LRTA BESTF" << endl;
		start();
		RealTimeSearch<SlidingTilePuzzle> lsslrtabestf(world, "a-star", "learn", "minimin", lookaheadDepth);
		lsslrtabestfRes = lsslrtabestf.search();
		end();
		if (!world.validatePath(lsslrtabestfRes.path)){
            cout << "Invalid path detected from LSS-LRTA BESTF search!" << endl;
            exit(1);
        }
		
		cout << "LSS-LRTA KBEST" << endl;
		start();
		RealTimeSearch<SlidingTilePuzzle> lsslrtakbest(world, "a-star", "learn", "k-best", lookaheadDepth);
		lsslrtakbestRes = lsslrtakbest.search();
		end();
		if (!world.validatePath(lsslrtakbestRes.path)){
            cout << "Invalid path detected from LSS-LRTA KBEST search!" << endl;
            exit(1);
        }
        
	} else if (domain == "HeavyTile")	{
		HeavyTilePuzzle world = HeavyTilePuzzle(cin);

		cout << "GUCTS-F" << endl;
        start();
		THTS_RT <HeavyTilePuzzle> thtsguctsf(world, "GUCTS-F", lookaheadDepth);
        guctsfRes = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(guctsfRes.path)){
            cout << "Invalid path detected from GUCTS-F search!" << endl;
            exit(1);
        }

		cout << "GUCTS" << endl;
        start();
		THTS_RT <HeavyTilePuzzle> thtsgucts(world, "GUCTS", lookaheadDepth);
		guctsRes = thtsgucts.getPlan();
		end();
		if (!world.validatePath(guctsRes.path)){
            cout << "Invalid path detected from GUCTS search!" << endl;
            exit(1);
        }
		
		cout << "WAS" << endl;
        start();
		THTS_RT <HeavyTilePuzzle> thtswa(world, "WAS", lookaheadDepth);
        wasRes = thtswa.getPlan();
		end();
		if (!world.validatePath(wasRes.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }

		cout << "FHAT" << endl;
		start();
		RealTimeSearch<HeavyTilePuzzle> fhat(world, "f-hat", "learn", "k-best", lookaheadDepth, 1, "normal");
		fhatRes = fhat.search();
		end();
		if (!world.validatePath(fhatRes.path)){
            cout << "Invalid path detected from FHAT search!" << endl;
            exit(1);
        }

		cout << "RISK" << endl;
		start();
		RealTimeSearch<HeavyTilePuzzle> risk(world, "risk", "learn", "k-best", lookaheadDepth, 1, "normal");
		riskRes = risk.search();
		end();
		if (!world.validatePath(riskRes.path)){
            cout << "Invalid path detected from RISK search!" << endl;
            exit(1);
        }

		cout << "LSS-LRTA BESTF" << endl;
		start();
		RealTimeSearch<HeavyTilePuzzle> lsslrtabestf(world, "a-star", "learn", "minimin", lookaheadDepth);
		lsslrtabestfRes = lsslrtabestf.search();
		end();
		if (!world.validatePath(lsslrtabestfRes.path)){
            cout << "Invalid path detected from LSS-LRTA BESTF search!" << endl;
            exit(1);
        }

		cout << "LSS-LRTA KBEST" << endl;
		start();
		RealTimeSearch<HeavyTilePuzzle> lsslrtakbest(world, "a-star", "learn", "k-best", lookaheadDepth);
		lsslrtakbestRes = lsslrtakbest.search();
		end();
		if (!world.validatePath(lsslrtakbestRes.path)){
            cout << "Invalid path detected from LSS-LRTA KBEST search!" << endl;
            exit(1);
        }

	} else {
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	string result = "FHAT," + domain + "," + to_string(fhatRes.solutionCost) + "," + to_string(fhatRes.nodesGenerated) + "," + to_string(fhatRes.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nRISK," + domain + "," + to_string(riskRes.solutionCost) + "," + to_string(riskRes.nodesGenerated) + "," + to_string(riskRes.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nLSS-LRTA-BESTF," + domain + "," + to_string(lsslrtabestfRes.solutionCost) + "," + to_string(lsslrtabestfRes.nodesGenerated) + "," + to_string(lsslrtabestfRes.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nLSS-LRTA-KBEST," + domain + "," + to_string(lsslrtakbestRes.solutionCost) + "," + to_string(lsslrtakbestRes.nodesGenerated) + "," + to_string(lsslrtakbestRes.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nWA-STAR," + domain + "," + to_string(wasRes.solutionCost) + "," + to_string(wasRes.nodesGenerated) + "," + to_string(wasRes.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nGUCT-STAR-F," + domain + "," + to_string(guctsfRes.solutionCost) + "," + to_string(guctsfRes.nodesGenerated) + "," + to_string(guctsfRes.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nGUCT-STAR," + domain + "," + to_string(guctsRes.solutionCost) + "," + to_string(guctsRes.nodesGenerated) + "," + to_string(guctsRes.nodesExpanded) + "," + to_string(lookaheadDepth);

	if (argc < 4){
		cout << result << endl;
	} else {
		ofstream out(argv[3]);
		out << result;
		out.close();
	}

}
