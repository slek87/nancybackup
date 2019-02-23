#include <iostream>
#include <fstream>
#include <string>
#include "../RealTimeSearch.h"
#include "../domain/PancakePuzzle.h"

using namespace std;

int main(int argc, char** argv) {
    PancakePuzzle world = PancakePuzzle(6, 1, 1);

    world.initialize("pancake", 1);
	PancakePuzzle::State cur = world.getStartState();
    cout << cur << endl;

}
