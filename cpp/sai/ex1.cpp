#include <iostream>
#include <string>
#include <fstream>
#include "trialbased.h"
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

    unordered_map <string, string> myMap;

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
    } else if (domain == "TreeWorld"){
        TreeWorld world = TreeWorld(cin);
        THTS <TreeWorld> as(world, "AS");
        THTS <TreeWorld> was(world, "WAS");
        THTS <TreeWorld> uct(world, "UCT");
        THTS <TreeWorld> guct(world, "GUCT");
        THTS <TreeWorld> ucts(world, "UCTS");
        THTS <TreeWorld> gucts(world, "GUCTS");
        as_Res = as.getPlan();
        was_Res = was.getPlan();
        uct_Res = uct.getPlan();
        guct_Res = guct.getPlan();
        ucts_Res = ucts.getPlan();
        gucts_Res = gucts.getPlan();
    } else if (domain == "SlidingPuzzle"){
        SlidingTilePuzzle world = SlidingTilePuzzle(cin);
        THTS <SlidingTilePuzzle> as(world, "AS");
        THTS <SlidingTilePuzzle> was(world, "WAS");
        THTS <SlidingTilePuzzle> uct(world, "UCT");
        THTS <SlidingTilePuzzle> guct(world, "GUCT");
        THTS <SlidingTilePuzzle> ucts(world, "UCTS");
        THTS <SlidingTilePuzzle> gucts(world, "GUCTS");
        as_Res = as.getPlan();
        was_Res = was.getPlan();
        uct_Res = uct.getPlan();
        guct_Res = guct.getPlan();
        ucts_Res = ucts.getPlan();
        gucts_Res = gucts.getPlan();
    } else if (domain == "HeavyTile"){
        HeavyTilePuzzle world = HeavyTilePuzzle(cin);
        THTS <HeavyTilePuzzle> as(world, "AS");
        THTS <HeavyTilePuzzle> was(world, "WAS");
        THTS <HeavyTilePuzzle> uct(world, "UCT");
        THTS <HeavyTilePuzzle> guct(world, "GUCT");
        THTS <HeavyTilePuzzle> ucts(world, "UCTS");
        THTS <HeavyTilePuzzle> gucts(world, "GUCTS");
        as_Res = as.getPlan();
        was_Res = was.getPlan();
        uct_Res = uct.getPlan();
        guct_Res = guct.getPlan();
        ucts_Res = ucts.getPlan();
        gucts_Res = gucts.getPlan();
    } else if (domain == "InverseTile"){
        InverseTilePuzzle world = InverseTilePuzzle(cin);
        THTS <InverseTilePuzzle> as(world, "AS");
        THTS <InverseTilePuzzle> was(world, "WAS");
        THTS <InverseTilePuzzle> uct(world, "UCT");
        THTS <InverseTilePuzzle> guct(world, "GUCT");
        THTS <InverseTilePuzzle> ucts(world, "UCTS");
        THTS <InverseTilePuzzle> gucts(world, "GUCTS");
        as_Res = as.getPlan();
        was_Res = was.getPlan();
        uct_Res = uct.getPlan();
        guct_Res = guct.getPlan();
        ucts_Res = ucts.getPlan();
        gucts_Res = gucts.getPlan();
    }
    myMap["A*"] =  "[" + to_string(as_Res.solutionCost) + ", " + to_string(as_Res.nodesGenerated)  + ", " + to_string(as_Res.nodesExpanded) + "]";
    myMap["WA*"] = "[" + to_string(was_Res.solutionCost) + ", " + to_string(was_Res.nodesGenerated)  + ", " + to_string(was_Res.nodesExpanded) + "]";
    myMap["UCT"] = "[" + to_string(uct_Res.solutionCost) + ", " + to_string(uct_Res.nodesGenerated)  + ", " + to_string(uct_Res.nodesExpanded) + "]";
    myMap["GUCT"] = "[" + to_string(guct_Res.solutionCost) + ", " + to_string(guct_Res.nodesGenerated)  + ", " + to_string(guct_Res.nodesExpanded) + "]";
    myMap["UCT*"] = "[" + to_string(ucts_Res.solutionCost) + ", " + to_string(ucts_Res.nodesGenerated)  + ", " + to_string(ucts_Res.nodesExpanded) + "]";
    myMap["GUCT*"] = "[" + to_string(gucts_Res.solutionCost) + ", " + to_string(gucts_Res.nodesGenerated)  + ", " + to_string(gucts_Res.nodesExpanded) + "]";

    string output = mapToJsonString(myMap);

    if ( argc < 3){
        cout << output << endl;
    } else {
        ofstream out(argv[2]);
        out << output;
        out.close();
    }

}
