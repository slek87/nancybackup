#include <iostream>
#include <string>
#include <fstream>
#include "TrialBasedRealTimeSearch_1.h"
#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"
#include "../domain/SimpleTilePuzzle.h"
#include "../domain/HeavyTilePuzzle.h"
#include "../domain/InverseTilePuzzle.h"
#include "../domain/PancakePuzzle.h"
#include "../domain/TreeWorld.h"
#include "../utility/ResultContainer.h"

using namespace std;


int main(int argc, char** argv) {
    if ( argc < 3){
		cout << "Wrong number of arguments: [executable] [domain] [expansion limit] [trial algorithm] [decision algorithm] [optional: output file] < [domain file]" << endl;
		exit(1);
	}

    ResultContainer res;
    string domain = argv[1];
    int lookahead = stoi(argv[2]);
    string algorithm = argv[3];
    // string prune_type = argv[3];
    string prune_type = "erase";
    // int lookahead = stoi(argv[4]);
    string decision = argv[4];

    if (decision == "-"){
        decision = "";
    }

    if (domain == "Pancake" || domain == "PancakeDPS" ){
        PancakePuzzle world = PancakePuzzle(cin);
        if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
        THTS_RT <PancakePuzzle> thts(world, algorithm, lookahead, decision);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
        if (!world.validatePath(res.path)) exit(1);
        
    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS_RT <TreeWorld> thts(world, algorithm, lookahead, decision);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS_RT <SlidingTilePuzzle> thts(world, algorithm, lookahead, decision);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
        if (!world.validatePath(res.path)) exit(1);

    } else if (domain == "HeavyTile"){
        HeavyTilePuzzle world = HeavyTilePuzzle(cin);
        THTS_RT <HeavyTilePuzzle> thts(world, algorithm, lookahead, decision);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "InverseTile"){
        InverseTilePuzzle world = InverseTilePuzzle(cin);
        THTS_RT <InverseTilePuzzle> thts(world, algorithm, lookahead, decision);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    }

    if (decision == "nancy"){
        algorithm = algorithm + "-N";
    } else if (decision == "fhat"){
        algorithm = algorithm + "-FHAT";
    } if (decision == "f"){
        algorithm = algorithm + "-F";
    }
    string result = algorithm + "," + domain + "," + to_string(res.solutionCost) + "," + to_string(res.nodesGenerated) + "," + to_string(res.nodesExpanded) + "," + to_string(lookahead);

    if (argc < 6) {
		cout << result << endl;
	} else {
		ofstream out(argv[5]);
		out << result;
		out.close();
	}
}