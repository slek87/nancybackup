#include <iostream>
#include <string>
#include <fstream>
#include "TrialBasedRealTimeSearch.h"
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
    ResultContainer res;
    string domain = argv[1];
    string algorithm = argv[2];
    // string prune_type = argv[3];
    string prune_type = "erase";
    // int lookahead = stoi(argv[4]);
    int lookahead = stoi(argv[3]);


    if (domain == "Pancake" || domain == "PancakeDPS" ){
        ResultContainer result;
        PancakePuzzle world = PancakePuzzle(cin);
        if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
        THTS_RT <PancakePuzzle> thts(world, algorithm, lookahead, "dijkstra");
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS_RT <TreeWorld> thts(world, algorithm, lookahead, "dijkstra");
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS_RT <SlidingTilePuzzle> thts(world, algorithm, lookahead, "dijkstra");
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "HeavyTile"){
        HeavyTilePuzzle world = HeavyTilePuzzle(cin);
        THTS_RT <HeavyTilePuzzle> thts(world, algorithm, lookahead, "dijkstra");
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "InverseTile"){
        InverseTilePuzzle world = InverseTilePuzzle(cin);
        THTS_RT <InverseTilePuzzle> thts(world, algorithm, lookahead, "dijkstra");
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    }

    cout << "{\"" + algorithm << "\":[" + to_string(res.solutionCost) + ", " + 
    to_string(res.nodesGenerated)  + ", " + to_string(res.nodesExpanded) + "]}" << endl;
}