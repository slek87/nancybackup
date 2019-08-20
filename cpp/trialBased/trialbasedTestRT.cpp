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
#include "../domain/SqrtTilePuzzle.h"
#include "../utility/ResultContainer.h"

using namespace std;


int main(int argc, char** argv) {
    if ( argc < 3){
		cout << "Wrong number of arguments: [executable] [domain] [expansion limit] [trial algorithm] [optional: output file] < [domain file]" << endl;
		exit(1);
	}

    ResultContainer res;
    string domain = argv[1];
    int lookahead = stoi(argv[2]);
    string algorithmInput = argv[3];
    string prune_type = "erase";
    bool greedyOneStep = false;
    bool hLearning = false;
    bool check = true; // Check validate solution

    string algorithm = "";
    bool front = true;


    for(int i = 0; i < algorithmInput.length(); ++i){
        if (algorithmInput[i] == '-'){
            front = !front;
        } else {
            if (front){
                algorithm += algorithmInput[i];
            } else {
                if (algorithmInput[i] == 'L'){
                    hLearning = true;
                } else if (algorithmInput[i] == 'H'){
                    greedyOneStep = true;
                } 
            }
        }
    }



    if (domain == "Pancake" || domain == "PancakeDPS" ){
        ResultContainer result;
        PancakePuzzle world = PancakePuzzle(cin);
        if (domain == "PancakeDPS"){
			world.setVariant(1);
		}
        THTS_RT <PancakePuzzle> thts(world, algorithm, lookahead, greedyOneStep, hLearning);

        thts.setRecordPlan(check);

        res = thts.getPlan();
        if (check && !world.validatePath(res.path)) {
            cout << "INVALID PATH!" << endl;
            exit(1);
        }
    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS_RT <TreeWorld> thts(world, algorithm, lookahead, greedyOneStep, hLearning);

        thts.setRecordPlan(check);

        res = thts.getPlan();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS_RT <SlidingTilePuzzle> thts(world, algorithm, lookahead, greedyOneStep, hLearning);

        thts.setRecordPlan(check);

        res = thts.getPlan();
        if (check && !world.validatePath(res.path)) {
            cout << "INVALID PATH!" << endl;
            exit(1);
        }

    } else if (domain == "HeavyTile"){
        HeavyTilePuzzle world = HeavyTilePuzzle(cin);
        THTS_RT <HeavyTilePuzzle> thts(world, algorithm, lookahead, greedyOneStep, hLearning);

        thts.setRecordPlan(check);

        res = thts.getPlan();
        if (check && !world.validatePath(res.path)) {
            cout << "INVALID PATH!" << endl;            
            exit(1);
        }
    } else if (domain == "InverseTile"){
        InverseTilePuzzle world = InverseTilePuzzle(cin);
        THTS_RT <InverseTilePuzzle> thts(world, algorithm, lookahead, greedyOneStep, hLearning);

        thts.setRecordPlan(check);

        res = thts.getPlan();
        if (check && !world.validatePath(res.path)) {
            cout << "INVALID PATH!" << endl;            
            exit(1);
        }
    } else if (domain == "SqrtTile"){
        SqrtTilePuzzle world = SqrtTilePuzzle(cin);
        THTS_RT <SqrtTilePuzzle> thts(world, algorithm, lookahead, greedyOneStep, hLearning);

        thts.setRecordPlan(check);

        res = thts.getPlan();
        if (check && !world.validatePath(res.path)) {
            cout << "INVALID PATH!" << endl;            
            exit(1);
        }
    }

    string result = algorithmInput + "," + domain + "," + to_string(res.solutionCost) + "," + to_string(res.nodesGenerated) + "," + to_string(res.nodesExpanded) + "," + to_string(lookahead);
    
    if (argc < 5) {
		cout << result << endl;
	} else {
		ofstream out(argv[4]);
		out << result;
		out.close();
	}
}