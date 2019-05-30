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

    if (domain == "Pancake" || domain == "PancakeDPS" ){
        ResultContainer result;
        PancakePuzzle world = PancakePuzzle(cin);
    
        if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
        THTS <PancakePuzzle> thts(world, algorithm);
        // thts.debug(false);
        // thts.setW(5);
        // res = thts.solve();
        // thts.printPlan();

        thts.getPlan();
    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS <TreeWorld> thts(world, algorithm);
        // res = thts.solve();
        // thts.printPlan();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS <SlidingTilePuzzle> thts(world, algorithm);
        // res = thts.solve();
        // thts.printPlan();
        thts.getPlan();

    }

    cout << to_string(res.solutionCost) << endl;
}