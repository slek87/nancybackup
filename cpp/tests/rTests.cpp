#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"
#include "../randomSearch.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc > 4 || argc < 3)
	{
		cout << "Wrong number of arguments: ./backupTestsAS <Domain Type> <lookahead depth> <optional: output file> < <domain file>" << endl;
		cout << "Available domains are TreeWorld and SlidingPuzzle" << endl;
		exit(1);
	}

	// Get the lookahead depth
	int lookaheadDepth = stoi(argv[2]);

	// Get the domain type
	string domain = argv[1];

    double randomCost;
	int ksamples;

    if (domain == "TreeWorld")
	{
        TreeWorld world = TreeWorld(cin);

        RandomSearch<TreeWorld> r(world, lookaheadDepth);
		randomCost = r.randomSearch();

        cout << "[Random walk]" << endl;
		cout << "Cost:\t" << randomCost << endl;

		RandomSearch<TreeWorld> r6(world, 6);
		randomCost = r6.randomSampling();
		cout << "[6]" << endl;
		cout << "Cost:\t" << randomCost << endl;

		RandomSearch<TreeWorld> r10(world, 10);
		randomCost = r10.randomSampling();
		cout << "[10]" << endl;
		cout << "Cost:\t" << randomCost << endl;

		RandomSearch<TreeWorld> r50(world, 50);
		randomCost = r50.randomSampling();
		cout << "[50]" << endl;
		cout << "Cost:\t" << randomCost << endl;

    }

}
