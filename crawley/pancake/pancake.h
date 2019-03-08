#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PancakeState{
    /* Incase we want to add more info */
    unsigned int * state;
} PancakeState;

typedef struct PancakeWorld{
    int size;
    int puzzleVariant;
    PancakeState * startingState;
    PancakeState * goalState;
} PancakeWorld;

bool is_goal(PancakeWorld* world, PancakeState* state);
double heuristic(PancakeWorld* world, PancakeState* state);
double distance(PancakeWorld* world, PancakeState* state);
void free_gridworld(PancakeWorld* world);
void printstate(PancakeWorld* world, PancakeState* state);
PancakeWorld* init_pancakeWorld(FILE *in);


