#include <stdio.h>
#include <stdlib.h>
#include "pancake.h"

int main() {
    FILE* input_file = fopen("1-16.pan", "r");
    PancakeWorld* pancakeWorld = init_pancakeWorld(input_file);
    PancakeState* the_successors;
    int i;
    int num_successors;
    fprintf(stdout, "pancake size:\n\t%d\n", pancakeWorld->size);

    fprintf(stdout, "starting state:\n\t");
    printstate(pancakeWorld, pancakeWorld->startingState);

    fprintf(stdout, "goal state:\n\t");
    printstate(pancakeWorld, pancakeWorld->goalState);

    fprintf(stdout, "h(init) %f\n", h(pancakeWorld, pancakeWorld->startingState));
    fprintf(stdout, "h(goal) %f\n", h(pancakeWorld, pancakeWorld->goalState));
    fprintf(stdout, "d(init) %f\n", d(pancakeWorld, pancakeWorld->startingState));

    the_successors = malloc(sizeof(PancakeState) * pancakeWorld->size - 1);
    num_successors = successors(pancakeWorld, pancakeWorld->startingState, the_successors);

    fprintf(stdout, "puzzle vairant:%d\n", pancakeWorld->puzzleVariant);

    for (i = 0; i < num_successors; ++i) {
        fprintf(stdout, "scsr:%d\n\t", i);
        printstate(pancakeWorld, &the_successors[i]);
        fprintf(stdout, "\tcost:%f\n", getedgecost(pancakeWorld, &the_successors[i]));
    }

    set_variant(pancakeWorld, 1);
    fprintf(stdout, "puzzle vairant:%d\n", pancakeWorld->puzzleVariant);
    for (i = 0; i < num_successors; ++i) {
        fprintf(stdout, "scsr:%d\n\t", i);
        printstate(pancakeWorld, &the_successors[i]);
        fprintf(stdout, "\tcost:%f\n", getedgecost(pancakeWorld, &the_successors[i]));
    }

    set_variant(pancakeWorld, 2);
    fprintf(stdout, "puzzle vairant:%d\n", pancakeWorld->puzzleVariant);
    for (i = 0; i < num_successors; ++i) {
        fprintf(stdout, "scsr:%d\n\t", i);
        printstate(pancakeWorld, &the_successors[i]);
        fprintf(stdout, "\tcost:%f\n", getedgecost(pancakeWorld, &the_successors[i]));
        free(the_successors[i].state);
    }
    fprintf(stdout, "init == init %d\n", equals(pancakeWorld->startingState, pancakeWorld->startingState));
    fprintf(stdout, "init != goal %d\n", equals(pancakeWorld->startingState, pancakeWorld->goalState));
    fprintf(stdout, "hash of init: %u\n", pancakeWorld->startingState->key);
    fprintf(stdout, "hash of goal: %u\n", pancakeWorld->goalState->key);
    free(the_successors);
    free_world(pancakeWorld);    
    return 0;
}