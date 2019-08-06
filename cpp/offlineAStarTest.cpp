#include <iostream>
#include <string>
#include <fstream>
#include "OfflineAStar.h"
#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"
#include "../domain/PancakePuzzle.h"
#include "../domain/TreeWorld.h"
#include "../utility/ResultContainer.h"

using namespace std;


int main(int argc, char** argv) {
    string domain = argv[1];
    ResultContainer res;

    if (domain == "Pancake" || domain == "PancakeDPS" ){
        PancakePuzzle world = PancakePuzzle(cin);
        if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
        ResultContainer result;
        OfflineAStar <PancakePuzzle> astar(world);
        res = astar.solve();
    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        OfflineAStar <TreeWorld> astar(world);
        res =astar.solve();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        OfflineAStar <SlidingTilePuzzle> astar(world);
        res = astar.solve();
    }

    cout << to_string(res.solutionCost) << endl;


}