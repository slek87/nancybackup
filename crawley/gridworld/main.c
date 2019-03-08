#include <stdio.h>
#include <stdlib.h>
#include "gridworld.h"

int main() {
    FILE* input_file = fopen("/home/aifs2/doylew/CLionProjects/gridworld/toy.vw", "r");
    GridWorld* gridWorld = init_gridworld(input_file);
    fprintf(stdout, "map size %d x %d\n", gridWorld->width, gridWorld->height);
    fprintf(stdout, "start: %d %d\n", gridWorld->startLocation->x, gridWorld->startLocation->y);
    fprintf(stdout, "goal: %d %d\n", gridWorld->targetLocation->x, gridWorld->targetLocation->y);
    GridWorldState* initialState = malloc(sizeof(GridWorldState));
    GridWorldState* goalState = malloc(sizeof(GridWorldState));
    Location agentLocation = {gridWorld->startLocation->x, gridWorld->startLocation->y};
    initialState->agentLocation = &agentLocation;
    Location agentGoal = {gridWorld->targetLocation->x, gridWorld->targetLocation->y};
    goalState->agentLocation = &agentGoal;
    bool legal_location = is_legal_location(gridWorld, initialState->agentLocation);
    bool goal_location = is_goal(gridWorld, goalState);
    fprintf(stdout, "hash of init: %d\n", hash(initialState));
    fprintf(stdout, "hash of goal: %d\n", hash(goalState));
    fprintf(stdout, "initial location legal: %d\n", legal_location);
    fprintf(stdout, "goal location is goal: %d\n", goal_location);
    fprintf(stdout, "init == init %d\n", equals(initialState, initialState));
    fprintf(stdout, "init != goal %d\n", equals(initialState, goalState));
    fprintf(stdout, "h(init) %f\n", heuristic(gridWorld, initialState));
    fprintf(stdout, "h(goal) %f\n", heuristic(gridWorld, goalState));
    fprintf(stdout, "d(init) %f\n", distance(gridWorld, initialState));
    GridWorldState* the_successors = malloc(sizeof(GridWorldState) * 4);
    int num_successors = successors(gridWorld, initialState, the_successors);
    fprintf(stdout, "num successors %d\n", num_successors);
    for (int i = 0; i < num_successors; ++i) {
        fprintf(stdout, "successor %d %d\n", the_successors[i].agentLocation->x, the_successors[i].agentLocation->y);
        free(the_successors[i].agentLocation);
    }
    free(the_successors);
    fclose(input_file);
    free_gridworld(gridWorld);
    free(initialState);
    free(goalState);
    return 0;
}