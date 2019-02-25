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


    // Testing hash used 12! = 479,001,600 combinations on galena (pc in ai lab)
    // 8! on local... Crappy CPU :( 8! = 40,320 combinations
    // Using char to save memeory
    // But also used int to make sure the hashes are still the same
    cout << "Testing hash..." << endl;
    vector<char> v;
    unordered_map<unsigned long long, char> hashes;

    for (int i = 1; i <= 8; ++i){
        v.push_back(i);
    }

    do {
        // cout << (int)v[0] << (int)v[1] << (int)v[2] << (int)v[3] << endl;
        int size = hashes.size();
        hashes[getHash(v)] = 0;
        if (size == hashes.size()){
            cout << "Hash collision deteceted!" << endl;
        }
    } while(std::next_permutation(v.begin(),v.end()));

    cout << "Initialize Pancake Puzzle Test... Parameters: " << size << " " << variant << " " << seed << endl;
    PancakePuzzle world = PancakePuzzle(6, 1, 1);

    world.initialize("policy", 1);
	State cur = world.getStartState();

    cout << "Testing << for start state..." << endl;
    cout << cur << endl;
    cout << endl;

    cout << "Getting heuristic for start state..." << endl;
    cout << world.heuristic(cur) << endl;
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
        cout << "[" << i << "] " << s.getLabel() << endl;
        cout << s << endl;
        cout << endl;
    }
    cout << endl;

    cout << "Getting label, distance, distanceErr, heuristic for each child..." << endl;
    for (int i = 0; i < children.size(); ++i){
        State s = children[i];
        Cost c;
        cout << "[" << i << "] " << s.getLabel() << ": ";
        cout << world.distance(s) << ", ";
        cout << world.distanceErr(s) << ", ";
        cout << world.heuristic(s) << endl;
    }
    cout << endl;


    
    
}
