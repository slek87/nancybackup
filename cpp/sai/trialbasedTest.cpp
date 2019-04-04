#include <iostream>
#include <string>
#include <fstream>
#include "trialbased.h"
#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"
#include "../domain/PancakePuzzle.h"
#include "../utility/ResultContainer.h"

using namespace std;


int main(int argc, char** argv) {

    ResultContainer result;
    PancakePuzzle world = PancakePuzzle(cin);
    // TreeWorld world = TreeWorld(cin);
    THTS <PancakePuzzle> thts(world);
    thts.solve();

}