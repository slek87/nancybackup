#include <iostream>
#include <string>
#include <fstream>
#include "trialbased.h"
#include "offlineastar.h"
#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"
#include "../domain/SimpleTilePuzzle.h"
#include "../domain/HeavyTilePuzzle.h"
#include "../domain/InverseTilePuzzle.h"
#include "../domain/PancakePuzzle.h"
#include "../domain/TreeWorld.h"
#include "../utility/ResultContainer.h"
#include <unordered_map>

using namespace std;

string mapToJsonString(unordered_map <string, string> & myMap){
    string jString = "{";
    int i = 0;
    for(auto it = myMap.begin(); it != myMap.end(); ++it){
        if (i > 0){
            jString += ", ";
        }
       jString += "\"" + it->first + "\":" + it->second;
       ++i;
    }
    jString += "}";
    return jString;
}

int main(int argc, char** argv) {
    ResultContainer as_Res;
    ResultContainer as_lockRes;
    ResultContainer oas_Res;


    unordered_map <string, string> myMap;

    string domain = argv[1];

    if (domain == "Pancake" || domain == "PancakeDPS" ){
        ResultContainer result;
        PancakePuzzle world = PancakePuzzle(cin);
        if (domain == "PancakeDPS"){
            world.setVariant(1);
        }
        THTS <PancakePuzzle> as(world, "AS");
        as_Res = as.getPlan();
        
        THTS <PancakePuzzle> asl(world, "AS");
        asl.setPruning("lock");
        as_lockRes = asl.getPlan();

        OfflineAStar <PancakePuzzle> oas(world);
        oas_Res = oas.solve();

    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS <TreeWorld> as(world, "AS");
        as_Res = as.getPlan();
        
        THTS <TreeWorld> asl(world, "AS");
        asl.setPruning("lock");
        as_lockRes = asl.getPlan();

        OfflineAStar <TreeWorld> oas(world);
        oas_Res = oas.solve();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS <SlidingTilePuzzle> as(world, "AS");
        as_Res = as.getPlan();
        
        THTS <SlidingTilePuzzle> asl(world, "AS");
        asl.setPruning("lock");
        as_lockRes = asl.getPlan();

        OfflineAStar <SlidingTilePuzzle> oas(world);
        oas_Res = oas.solve();
    } else if (domain == "HeavyTile"){
        HeavyTilePuzzle world = HeavyTilePuzzle(cin);
        THTS <HeavyTilePuzzle> as(world, "AS");
        as_Res = as.getPlan();
        
        THTS <HeavyTilePuzzle> asl(world, "AS");
        asl.setPruning("lock");
        as_lockRes = asl.getPlan();

        OfflineAStar <HeavyTilePuzzle> oas(world);
        oas_Res = oas.solve();
    } else if (domain == "InverseTile"){
        InverseTilePuzzle world = InverseTilePuzzle(cin);
        THTS <InverseTilePuzzle> as(world, "AS");
        as_Res = as.getPlan();
        
        THTS <InverseTilePuzzle> asl(world, "AS");
        asl.setPruning("lock");
        as_lockRes = asl.getPlan();

        OfflineAStar <InverseTilePuzzle> oas(world);
        oas_Res = oas.solve();
    }

    myMap["A*"] =  "[" + to_string(oas_Res.solutionCost) + ", " + to_string(oas_Res.nodesGenerated)  + ", " + to_string(oas_Res.nodesExpanded) + "]";
    myMap["THTS-A*"] =  "[" + to_string(as_Res.solutionCost) + ", " + to_string(as_Res.nodesGenerated)  + ", " + to_string(as_Res.nodesExpanded) + "]";
    myMap["THTS-A*-L"] =  "[" + to_string(as_lockRes.solutionCost) + ", " + to_string(as_lockRes.nodesGenerated)  + ", " + to_string(as_lockRes.nodesExpanded) + "]";

    string output = mapToJsonString(myMap);

    if ( argc < 3){
        cout << output << endl;
    } else {
        ofstream out(argv[2]);
        out << output;
        out.close();
    }

}
