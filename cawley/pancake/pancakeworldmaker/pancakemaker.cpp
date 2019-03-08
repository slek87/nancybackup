#include <iostream>
#include <unordered_map>
#include <functional>
#include <math.h> 
#include <algorithm>
#include <vector>

using namespace std;

void makepancake(int len){
    vector<int> startOrdering;
    vector<int> endOrdering;
    unordered_map<int, int> numbers;


    // Generating random unique numbers
    while (startOrdering.size() < len){
        int tmp = numbers.size();
        int rr = rand() % len + 1;
        numbers[rr] = 0;
        if (tmp != numbers.size()){
            startOrdering.push_back(rr);
        }
    }

    endOrdering = startOrdering;
    sort(endOrdering.begin(), endOrdering.end());

    cout << len << endl; 
    cout << "starting positions pancake:" << endl;
    for (int i : startOrdering){
        cout << i << endl;
    }
    cout << "end positions pancake:" << endl;
        for (int i : endOrdering){
        cout << i << endl;
    }
}

int main(int argc, char** argv){
    int len = stoi(argv[1]);
    srand(time(NULL));
    makepancake(len);
    

    return 0;
}