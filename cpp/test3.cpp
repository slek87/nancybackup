#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include "trialBased/TrialBasedRealTimeSearch.h"
#include "domain/TreeWorld.h"
#include "domain/SlidingTilePuzzle.h"
#include "domain/SimpleTilePuzzle.h"
#include "domain/HeavyTilePuzzle.h"
#include "domain/InverseTilePuzzle.h"
#include "domain/PancakePuzzle.h"
#include "domain/TreeWorld.h"
#include "utility/ResultContainer.h"
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

	ResultContainer wasRes;
	ResultContainer was0;
	ResultContainer was05;
	ResultContainer was15;


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
		
		cout << "WAS" << endl;		        
		start();
		THTS_RT <PancakePuzzle> thtsguctsf(world, "WAS", lookaheadDepth);
        thtsguctsf.setK(0); was0 = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(was0.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }
		

		cout << "WAS" << endl;
		start();
		THTS_RT <PancakePuzzle> thtsgucts(world, "WAS", lookaheadDepth);
		thtsgucts.setK(0.5); was05 = thtsgucts.getPlan();
		end();
		if (!world.validatePath(was05.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }

		cout << "WAS" << endl;
		start();
		THTS_RT <PancakePuzzle> thts15(world, "WAS", lookaheadDepth);
		thts15.setK(1.5); was15 = thts15.getPlan();
		end();
		if (!world.validatePath(was15.path)){
            cout << "Invalid path detected from WAS search!" << endl;
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


	} else if (domain == "TreeWorld"){
		TreeWorld world = TreeWorld(cin);

		cout << "WAS" << endl;		        
		start();
		THTS_RT <TreeWorld> thtsguctsf(world, "WAS", lookaheadDepth);
        thtsguctsf.setK(0); was0 = thtsguctsf.getPlan();
		end();
        
		cout << "WAS" << endl;
		start();
		THTS_RT <TreeWorld> thtsgucts(world, "WAS", lookaheadDepth);
		thtsgucts.setK(0.5); was05 = thtsgucts.getPlan();
		end();

		cout << "WAS" << endl;
		start();
		THTS_RT <TreeWorld> thts15(world, "WAS", lookaheadDepth);
		thts15.setK(1.5); was15 = thts15.getPlan();
		end();

		cout << "WAS" << endl;
		start();
		THTS_RT <TreeWorld> thtswa(world, "WAS", lookaheadDepth);
        wasRes = thtswa.getPlan();
		end();


        
	} else if (domain == "SlidingPuzzle")	{
		SlidingTilePuzzle world = SlidingTilePuzzle(cin);
		
		cout << "WAS" << endl;
		start();
		THTS_RT <SlidingTilePuzzle> thtsguctsf(world, "WAS", lookaheadDepth);
        thtsguctsf.setK(0); was0 = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(was0.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }
        
		cout << "WAS" << endl;
		start();
		THTS_RT <SlidingTilePuzzle> thtsgucts(world, "WAS", lookaheadDepth);
		thtsgucts.setK(0.5); was05 = thtsgucts.getPlan();
		end();
		if (!world.validatePath(was05.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }

		cout << "WAS" << endl;
		start();
		THTS_RT <SlidingTilePuzzle> thts15(world, "WAS", lookaheadDepth);
		thts15.setK(1.5); was15 = thts15.getPlan();
		end();
		if (!world.validatePath(was15.path)){
            cout << "Invalid path detected from WAS search!" << endl;
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


        
	} else if (domain == "HeavyTile")	{
		HeavyTilePuzzle world = HeavyTilePuzzle(cin);

		cout << "WAS" << endl;
        start();
		THTS_RT <HeavyTilePuzzle> thtsguctsf(world, "WAS", lookaheadDepth);
        thtsguctsf.setK(0); was0 = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(was0.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }

		cout << "WAS" << endl;
        start();
		THTS_RT <HeavyTilePuzzle> thtsgucts(world, "WAS", lookaheadDepth);
		thtsgucts.setK(0.5); was05 = thtsgucts.getPlan();
		end();
		if (!world.validatePath(was05.path)){
            cout << "Invalid path detected from WAS search!" << endl;
            exit(1);
        }
		
		cout << "WAS" << endl;
		start();
		THTS_RT <HeavyTilePuzzle> thts15(world, "WAS", lookaheadDepth);
		thts15.setK(1.5); was15 = thts15.getPlan();
		end();
		if (!world.validatePath(was15.path)){
            cout << "Invalid path detected from WAS search!" << endl;
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

	

	} else {
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	string result = "WA-STAR," + domain + "," + to_string(wasRes.solutionCost) + "," + to_string(wasRes.nodesGenerated) + "," + to_string(wasRes.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nWA-STAR k-0," + domain + "," + to_string(was0.solutionCost) + "," + to_string(was0.nodesGenerated) + "," + to_string(was0.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nWA-STAR k-1.5," + domain + "," + to_string(was15.solutionCost) + "," + to_string(was15.nodesGenerated) + "," + to_string(was15.nodesExpanded) + "," + to_string(lookaheadDepth);
	result += "\nWA-STAR k=0.5," + domain + "," + to_string(was05.solutionCost) + "," + to_string(was05.nodesGenerated) + "," + to_string(was05.nodesExpanded) + "," + to_string(lookaheadDepth);

	if (argc < 4){
		cout << result << endl;
	} else {
		ofstream out(argv[3]);
		out << result;
		out.close();
	}

}
