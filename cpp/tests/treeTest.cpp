#include <iostream>
#include <fstream>
#include <string>
#include "../RealTimeSearch.h"
#include "../domain/TreeWorld.h"

using namespace std;
typedef typename TreeWorld::State State;

int main(int argc, char** argv) {
    int size = 6;
    int variant = 1;
    int seed = 1;

    cout << "Initialize Sliding Puzzle Test..." << endl;
    TreeWorld world = TreeWorld(cin);

    world.initialize("policy", 1);
	State cur = world.getStartState();

    cout << "Testing << for start state..." << endl;
    cout << cur << endl;
    cout << endl;

    cout << "Testing toString() for start state..." << endl;
    cout << cur.toString() << endl;
    cout << endl;

    cout << "Testing first successors call..." << endl;
    vector<State> children = world.successors(cur);
    for (int i = 0; i < children.size(); ++i){
        State s = children[i];
        cout << "[" << i << "]" << s.getLabel() << endl;
        cout << s << endl;
        cout << endl;
    }
    cout << endl;

    cout << "Getting label, distance, distanceErr, heuristic for each child..." << endl;
    for (int i = 0; i < children.size(); ++i){
        State s = children[i];
        cout << "[" << i << "] " << s.getLabel() << " ";
        cout << world.distance(s) << ", ";
        cout << world.distanceErr(s) << ", ";
        cout << world.heuristic(s) << endl;
    }
    cout << endl;
   
    
}
