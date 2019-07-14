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
	ResultContainer guctsnRes;

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
		
		cout << "GUCTS-N" << endl;		        
		start();
		THTS_RT <PancakePuzzle> thtsguctsf(world, "GUCTS-N", lookaheadDepth);
        guctsnRes = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(guctsnRes.path)){
            cout << "Invalid path detected from GUCTS-N search!" << endl;
            exit(1);
        }
		

	} else if (domain == "TreeWorld"){
		TreeWorld world = TreeWorld(cin);

		cout << "GUCTS-N" << endl;		        
		start();
		THTS_RT <TreeWorld> thtsguctsf(world, "GUCTS-N", lookaheadDepth);
        guctsnRes = thtsguctsf.getPlan();
		end();
        
		
        
	} else if (domain == "SlidingPuzzle")	{
		SlidingTilePuzzle world = SlidingTilePuzzle(cin);
		
		cout << "GUCTS-N" << endl;
		start();
		THTS_RT <SlidingTilePuzzle> thtsguctsf(world, "GUCTS-N", lookaheadDepth);
        guctsnRes = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(guctsnRes.path)){
            cout << "Invalid path detected from GUCTS-N search!" << endl;
            exit(1);
        }
        
		
        
	} else if (domain == "HeavyTile")	{
		HeavyTilePuzzle world = HeavyTilePuzzle(cin);

		cout << "GUCTS-N" << endl;
        start();
		THTS_RT <HeavyTilePuzzle> thtsguctsf(world, "GUCTS-N", lookaheadDepth);
        guctsnRes = thtsguctsf.getPlan();
		end();
		if (!world.validatePath(guctsnRes.path)){
            cout << "Invalid path detected from GUCTS-N search!" << endl;
            exit(1);
        }

	} else {
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	string result = "GUCT-STAR-N," + domain + "," + to_string(guctsnRes.solutionCost) + "," + to_string(guctsnRes.nodesGenerated) + "," + to_string(guctsnRes.nodesExpanded) + "," + to_string(lookaheadDepth);

	if (argc < 4){
		cout << result << endl;
	} else {
		ofstream out(argv[3]);
		out << result;
		out.close();
	}

}
