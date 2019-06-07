#pragma once
#include "trialbased.h"

using namespace std;

template <class Domain>
class THTS_RT : public THTS {
public:
    using THTS::THTS;

    void performTrial(){
        // cout << "Perform Trial:_______________________________________" << endl;

        PQueue backupQueue;
        shared_ptr<Node> n = root;

        while (n->initialized){
            State old = n->state;
            selectAction(n);
            if (old == n->state){
                // cout << "Deadend..." << endl;
                exit(1);
            }
            // cout << "At:\n" << n->state << "\n" << endl;
        }


protected:
    int lookahead = 1;

};