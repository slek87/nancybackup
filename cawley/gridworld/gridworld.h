//
// Created by doylew on 3/6/19.
//

#ifndef GRIDWORLD_GRIDWORLD_H
#define GRIDWORLD_GRIDWORLD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Location{
    int x;
    int y;
} Location;

typedef struct GridWorldState{
    Location* agentLocation;
} GridWorldState;

typedef struct GridWorld{
    unsigned int width;
    unsigned int height;
    Location* startLocation;
    Location* relativeLocation; //= { {-1, 0}, {0, 1}, {0, -1}, {1, 0} } LEFT, DOWN, UP, RIGHT
    Location* blockedCells;
    Location* targetLocation;
} GridWorld;


GridWorld* init_gridworld(FILE *in);
void free_gridworld(GridWorld* gridWorld);

int successors(GridWorld* gridWorld, GridWorldState* state, GridWorldState* successors);
bool is_legal_location(GridWorld* gridWorld, Location* location);
double heuristic(GridWorld* gridWorld, GridWorldState* state);
double distance(GridWorld* gridWorld, GridWorldState* state);
bool is_goal(GridWorld* gridWorld, GridWorldState* state);

int hash(GridWorldState* gridWorldState);
int equals(GridWorldState* gridWorldState, GridWorldState* other);

#endif //GRIDWORLD_GRIDWORLD_H
