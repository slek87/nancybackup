#include <iostream>
#include <string>
#include <fstream>
#include "trialbased.h"
#include "../domain/TreeWorld.h"
#include "../domain/SlidingTilePuzzle.h"
#include "../domain/PancakePuzzle.h"
#include "../domain/TreeWorld.h"
#include "../utility/ResultContainer.h"
#include <unordered_map>

using namespace std;

string mapToJsonString(unordered_map& <string, double> myMap){
    string jString = "{";
    int i = 0;
    for(auto it = myMap.begin(); it != myMap.end(); ++it){
        if (i > 0){
            jString += ",";
        }
       jString += "\"" + it->first + "\":\"" + it->second + "\"";
       ++i;
    }
    jString += "}";
    return jString;
}

int main(int argc, char** argv) {
    ResultContainer as_Res;
    ResultContainer was_Res;
    ResultContainer uct_Res;
    ResultContainer guct_Res;
    ResultContainer ucts_Res;
    ResultContainer gucts_Res;
    ResultContainer as_lockRes;
    ResultContainer was_lockRes;
    ResultContainer uct_lockRes;
    ResultContainer guct_lockRes;
    ResultContainer ucts_lockRes;
    ResultContainer gucts_lockRes;

    unordered_map <string, double> myMap;

    if ( argc < 2){
        cout << "Wrong number of arguments: ./expansion1.sh DomainType [output file] < domainFile" << endl;
        cout << "Available domains are Pancake, PancakeDPS, TreeWorld and SlidingPuzzle" << endl;
        exit(1);
    }

    string domain = argv[1];

    if (domain == "Pancake" || domain == "PancakeDPS" ){
        ResultContainer result;
        PancakePuzzle world = PancakePuzzle(cin);

        if (domain == "PancakeDPS"){
            world.setVariant(1);
        }
        THTS <PancakePuzzle> as(world, "AS");
        THTS <PancakePuzzle> was(world, "WAS");
        THTS <PancakePuzzle> uct(world, "UCT");
        THTS <PancakePuzzle> guct(world, "GUCT");
        THTS <PancakePuzzle> ucts(world, "UCTS");
        THTS <PancakePuzzle> gucts(world, "GUCTS");

        as_Res = as.getPlan();
        was_Res = was.getPlan();
        uct_Res = uct.getPlan();
        guct_Res = guct.getPlan();
        ucts_Res = ucts.getPlan();
        gucts_Res = gucts.getPlan();

        myMap["A*"] = as_Res.solutionCost();
        myMap["WA*"] = was_Res.solutionCost();
        myMap["UCT"] = uct_Res.solutionCost();
        myMap["GUCT"] = guct_Res.solutionCost();
        myMap["UCT*"] = ucts_Res.solutionCost();
        myMap["GUCT*"] = gucts_Res.solutionCost();

    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS <PancakePuzzle> as(world, "AS");
        THTS <PancakePuzzle> was(world, "WAS");
        THTS <PancakePuzzle> uct(world, "UCT");
        THTS <PancakePuzzle> guct(world, "GUCT");
        THTS <PancakePuzzle> ucts(world, "UCTS");
        THTS <PancakePuzzle> gucts(world, "GUCTS");

        as_Res = as.getPlan();
        was_Res = was.getPlan();
        uct_Res = uct.getPlan();
        guct_Res = guct.getPlan();
        ucts_Res = ucts.getPlan();
        gucts_Res = gucts.getPlan();

        myMap["A*"] = as_Res.solutionCost();
        myMap["WA*"] = was_Res.solutionCost();
        myMap["UCT"] = uct_Res.solutionCost();
        myMap["GUCT"] = guct_Res.solutionCost();
        myMap["UCT*"] = ucts_Res.solutionCost();
        myMap["GUCT*"] = gucts_Res.solutionCost();

    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS <SlidingTilePuzzle> thts(world, algorithm);
        THTS <PancakePuzzle> as(world, "AS");
        THTS <PancakePuzzle> was(world, "WAS");
        THTS <PancakePuzzle> uct(world, "UCT");
        THTS <PancakePuzzle> guct(world, "GUCT");
        THTS <PancakePuzzle> ucts(world, "UCTS");
        THTS <PancakePuzzle> gucts(world, "GUCTS");

        as_Res = as.getPlan();
        was_Res = was.getPlan();
        uct_Res = uct.getPlan();
        guct_Res = guct.getPlan();
        ucts_Res = ucts.getPlan();
        gucts_Res = gucts.getPlan();

        myMap["A*"] = as_Res.solutionCost();
        myMap["WA*"] = was_Res.solutionCost();
        myMap["UCT"] = uct_Res.solutionCost();
        myMap["GUCT"] = guct_Res.solutionCost();
        myMap["UCT*"] = ucts_Res.solutionCost();
        myMap["GUCT*"] = gucts_Res.solutionCost();
    }

    string output = mapToJsonString(myMap);

    if ( argc < 3){
        cout << output << endl;
    } else {
        ofstream out(argv[2]);
        out << output;
        out.close();
    }

}
