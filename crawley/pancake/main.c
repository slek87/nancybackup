#include <stdio.h>
#include <stdlib.h>
#include "pancake.h"

int main() {
    FILE* input_file = fopen("1-16.pan", "r");
    PancakeWorld* pancakeWorld = init_pancakeWorld(input_file);

    fprintf(stdout, "pancake size %d\n", pancakeWorld->size);
    printstate(pancakeWorld, pancakeWorld->startingState);
    printstate(pancakeWorld, pancakeWorld->goalState);



    return 0;
}