#include "pancake.h"
#include <string.h>
/* https://stackoverflow.com/questions/28986265/converting-gets-string-into-an-integer-in-c 
https://www.daniweb.com/programming/software-development/code/216411/reading-a-file-line-by-line
*/
bool is_goal(PancakeWorld* world, PancakeState* state){
    return false;
}

double heuristic(PancakeWorld* world, PancakeState* state){
    /* Using gap heuristic from - Landmark Heuristics for the Pancake Problem */
    int size = world->size;
		int plate = size + 1;
		int sum = 0;
        int dif;
        int i;
		for (i = 1; i < size; ++i ){
			dif = state->state[i - 1] - state->state[i]; 
			if (dif > 1 || dif < -1)
				++sum;
		}
		dif = state->state[size - 1] - plate;
		if (dif > 1 || dif < -1)
			++sum;
		return sum;
}

double distance(PancakeWorld* world, PancakeState* state){
    return heuristic(world, state);
}

void printstate(PancakeWorld* world, PancakeState* state) {
    int i;
    for(i = 0; i < world->size; ++i){
        fprintf(stdout, "%d ", state->state[i]);
    } fprintf(stdout, "\n");
}

void free_world(PancakeWorld* world){
    free(world->startingState);
    free(world->goalState);
    free(world);
}

PancakeWorld* init_pancakeWorld(FILE *in){
    PancakeWorld* world = malloc(sizeof(PancakeWorld));
    unsigned int ptr;
    unsigned int size;
    int i;
    char c[32];
    PancakeState* startingState = malloc(sizeof(PancakeState));
    PancakeState* goalState = malloc(sizeof(PancakeState));
    fscanf(in, "%u", &size);
    world->size = size;
    startingState->state = malloc(sizeof(unsigned int) * size);
    goalState->state = malloc(sizeof(unsigned int) * size);

    fscanf(in,"%[^\n]", c);


    for(i = 0; i < size; ++i){
        fscanf(in, "%u", &ptr);
        startingState->state[i] = ptr;
    }

    fscanf(in,"%[^\n]", c); 

    for(i = 0; i < size; ++i){
        fscanf(in, "%u", &ptr);
        goalState->state[i] = ptr;
    }

    world->goalState = goalState;
    world->startingState = startingState;
    world->puzzleVariant = 0; /*default*/


    return world;
}

