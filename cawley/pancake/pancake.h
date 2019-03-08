#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PancakeState{
    int action;
    unsigned int key;
    unsigned char * state;
} PancakeState;

typedef struct PancakeWorld{
    int size;
    int puzzleVariant;
    PancakeState * startingState;
    PancakeState * goalState;
} PancakeWorld;

double h(PancakeWorld* world, PancakeState* state);
double d(PancakeWorld* world, PancakeState* state);
double getedgecost(PancakeWorld* world, PancakeState* state);
void free_world(PancakeWorld* world);
bool is_goal(PancakeWorld* world, PancakeState* state);
void printstate(PancakeWorld* world, PancakeState* state);
void set_variant(PancakeWorld* world, int variant);
int successors(PancakeWorld* world, PancakeState* state, PancakeState* successors);
PancakeWorld* init_pancakeWorld(FILE *in);
bool equals(PancakeState* state, PancakeState* other);
bool is_goal(PancakeWorld* world, PancakeState* state);

