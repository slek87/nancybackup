#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int s; // State.
    int N; // Children.
    int f; // Estimted f.
    int v; // Number of visits.
    int l; // Lock.
} Node;

typedef struct Task{
    int V;  // V is a finite set of domain state variable v
            // each with a doman D_v
    int s_0; // s_0 is the initial state
    int S_star; // set of goal state over V
    int O; // set of operators 

} Task;


void initalizeNode(Node* n){
    // for each actioni... In this case for each children?
    int children = 1;
    for (int i = 0; i < 1; ++i){
        int s = 0; // s' <- succ(s(n), o)
        
        // If s' not in TT and not is not deadend then
        if(true){
            // n' <- <s', 0, w*h(s'), l, isGoal(s')>
            //TT[s'] <- n'
            //N(n) <- N(n) union {n'} N = succesor nodes
        } else if (true) {
            // ELse if g(n) + c(o) < g(TT[s'])
            // backupQueue.insert(par(TT[s']))
            // N(par(TT[s'])) <- N(par(TT[s'])) \ {n'}
            // g(TT[s']) = g(n) + c(o)
            // N(n) <- N(n) union {TT[s']}

        }
    }
}

void backUp(Node* n){
    // THTS-BFS
    // f(n) <- min (n' in N(n)) { f(n') + k * c(n, n') }
    // v(n) <- sum of n' in N(n) {v(n')}
    // l(n) <-
}

Node* selectAction(Node* n){
    // THTS_BFS
    // TODO

    return NULL;
}

void performTrial(){
    Node* n = new Node(); // n <- n_0
    while (n){
        n = selectAction(n);
    }

    // If n is goal
    if (n)
        return; // Extract plan and return
    
    initalizeNode(n);

    // backupQueue.insert(n)

    // while backupQueue is not empty do
    while (true){
        n = NULL; // m <-backupQueue.pop()
        backUp(n);
        // if n != n_0
        //   backupQueue.insert(part(n))
    }

}

void thts(){
    // while time allows and no plan found do
    performTrial();
    // return plan
}