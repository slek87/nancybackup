#include <iostream>
#include <fstream>
#include <string>
#include "../RealTimeSearch.h"
#include "../domain/PancakePuzzle.h"

using namespace std;
typedef typename PancakePuzzle::State State;
typedef typename PancakePuzzle::Cost Cost;
typedef double Cost;


unsigned long long getHash(vector<char> s){
    return std::hash<std::string>() ( std::string( s.begin(), s.end())) ;
}


int main(int argc, char** argv) {
    int size = 6;
    int variant = 1;
    int seed = 1;


    // Testing hash using 12! = 479,001,600 permutations
    // Using char to save memeory
    vector<char> v;
    vector< vector<char> > w;
    for (int i = 1; i <= 12; ++i){
        v.push_back(i);
    }

    do {
        w.push_back(v);
    } while(std::next_permutation(v.begin(),v.end()));

    unordered_map<unsigned long long, char> hashes;

    for (vector<char> x : w){
        int size = hashes.size();
        hashes[getHash(x)] = 0;
        if (size == hashes.size()){
            cout << "Hash collision deteceted!" << endl;
        }
    }

    exit(0);







    cout << "Initialize Pancake Puzzle Test... Parameters: " << size << " " << variant << " " << seed << endl;
    PancakePuzzle world = PancakePuzzle(6, 1, 1);

    world.initialize("policy", 1);
	State cur = world.getStartState();

    cout << "Testing << for start state..." << endl;
    cout << cur << endl;
    cout << endl;

    cout << "Testing toString() for start state..." << endl;
    cout << cur.toString() << endl;
    cout << endl;

    std::vector<int> endOrdering = world.endOrdering;
    cout << "Printing end state..." << endl;

    for (int r = 0; r < endOrdering.size(); r++)    {
        cout << std::setw(3) << endOrdering[r] << " ";
    }
    cout << "\n" << endl;
    
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
        Cost c;
        cout << "[" << i << "] " << s.getLabel() << " ";
        c = world.distance(s);
        // cout << c << ", ";
        //cout << world.distance(s) << ", ";
        // cout << world.distanceErr(s) << ", ";
        // cout << world.heuristic(s) << endl;
    }
    cout << endl;


    
    
}
