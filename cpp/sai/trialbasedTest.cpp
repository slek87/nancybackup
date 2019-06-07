#include <iostream>
#include <string>
#include <fstream>
#include "trialbased.h"
#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"
#include "../domain/PancakePuzzle.h"
#include "../domain/TreeWorld.h"
#include "../utility/ResultContainer.h"

using namespace std;


int main(int argc, char** argv) {
    ResultContainer res;
    string domain = argv[1];
    string algorithm = argv[2];
    string prune_type;
    if (argc > 3){
        prune_type = argv[3];
        cout << prune_type << endl;
    }

    if (domain == "Pancake" || domain == "PancakeDPS" ){
        ResultContainer result;
        PancakePuzzle world = PancakePuzzle(cin);
        if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
        THTS <PancakePuzzle> thts(world, algorithm);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS <TreeWorld> thts(world, algorithm);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS <SlidingTilePuzzle> thts(world, algorithm);
        if (prune_type == "lock"){
            thts.setPruning(prune_type);
        }
        res = thts.getPlan();
    }

    cout << "solutionCost: " + to_string(res.solutionCost) << endl;
    cout << "nodesGenerated: " + to_string(res.nodesGenerated) << endl;
	cout << "nodesExpanded: " + to_string(res.nodesExpanded) << endl;
}