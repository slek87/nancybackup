#include "pancake.h"
#include <string.h>

unsigned int hash(PancakeWorld* world, PancakeState* state) {
    /* 
        FNV-1a
    */
    unsigned int offset_basis = 0x811C9DC5;
    unsigned int fnv_prime = 0x1000193;
    int i;
    for(i = 0; i < world->size; ++i) {
        unsigned char value = state->state[i];
        offset_basis = offset_basis ^ value;
        offset_basis *= fnv_prime;
    }
    return offset_basis;
} 

static void init_state(PancakeWorld* world, PancakeState* state, int loc){
    int start = 0;
    int end = loc;
    state->state = malloc(sizeof(int) * world->size);
    /* flipordering */
    while(start <= end){    
        state->state[end] = world->startingState->state[start];
        state->state[start] = world->startingState->state[end];
        ++start;
        --end;
    } 
    for(start = loc + 1; start < world->size; ++start){
        state->state[start] = world->startingState->state[start];
    }
    state->action = loc;
    state->key =  hash(world, state);
}

int successors(PancakeWorld* world, PancakeState* state, PancakeState* successors){
    int num_successors = 0;
    int i;
    for (i = world->size - 1; i > 0; --i){
        init_state(world, &successors[num_successors], i);
        ++num_successors;    
    }
    return num_successors;
}

bool equals(PancakeState* state, PancakeState* other){
    return state->key == other->key;
}


bool is_goal(PancakeWorld* world, PancakeState* state){
    return world->goalState->key == state->key;
}

static int gapheuristic(PancakeWorld* world, PancakeState* state){
    /* Using gap heuristic from - Landmark Heuristics for the Pancake Problem */
    int size = world->size;
    int plate = size + 1;
    int sum = 0;
    int dif;
    int i;
    int x;
    int y;
    for (i = 1; i < size; ++i ){
        x = state->state[i - 1];
        y = state->state[i];
        dif = x - y;
        if (dif > 1 || dif < -1){
            if (world->puzzleVariant == 0){
                ++sum;
            } else {
                if ( x < y){
                    sum += x;
                } else {
                    sum += y;
                }
            }
        }
    }
    x = state->state[size - 1];
    dif = x - plate;
    if (dif > 1 || dif < -1){
        if (world->puzzleVariant == 0){
            ++sum;
        } else {
            sum += x;
        }
    }
    return sum;
}

double h(PancakeWorld* world, PancakeState* state){
    return gapheuristic(world, state);
}

double d(PancakeWorld* world, PancakeState* state){
    /* If the edge cost is required clled getEdgeCose */
    return gapheuristic(world, state);
}

double getedgecost(PancakeWorld* world, PancakeState* state){
        /* Returns a cost from the predessor */

		int l = state->action;
        /* 
        1: Cost is max of two elements of each end of the set being flipped. 
        */
		if (world->puzzleVariant == 1){
			int i = state->state[0];
			int j = state->state[l];
			if ( i > j)
				return i;
			return j; 
		}

        /*
        2: Each pancake has a weight, equal to its index. 
          The cost is the sum of the indexes of pancakes being flipped.
        */
		if (world->puzzleVariant == 2){
			int sum = 0;
            int i;
			for (i = 1; i <= l; ++i) {
				sum += i;
			}
			return sum;
		}

        /* 0: Regular pancake puzzle, where each flip cost 1. */
		return 1; 
	}

void printstate(PancakeWorld* world, PancakeState* state) {
    int i;
    for(i = 0; i < world->size; ++i){
        fprintf(stdout, "%d ", (int) state->state[i]);
    } fprintf(stdout, "\n");
}

void free_world(PancakeWorld* world){
    free(world->startingState->state);
    free(world->startingState);
    free(world->goalState->state);
    free(world->goalState);
    free(world);
}

void set_variant(PancakeWorld* world, int variant){
    if (variant < 0 || variant > 2){
        fprintf(stdout, "Invalid variant!\n");
        exit(-1);
    }
    world->puzzleVariant = variant;
}

PancakeWorld* init_pancakeWorld(FILE *in){
    PancakeWorld* world = malloc(sizeof(PancakeWorld));
    unsigned int ptr;
    int size;
    int i;
    char c;
    PancakeState* startingState = malloc(sizeof(PancakeState));
    PancakeState* goalState = malloc(sizeof(PancakeState));

    if (fscanf(in, "%d", &size) != 1) {
        fprintf(stdout, "Failed to read\n");
        exit(-1);
    }
    world->size = size;
    startingState->state = malloc(sizeof(unsigned char) * size);
    startingState->action = 0;
    goalState->state = malloc(sizeof(unsigned char) * size);
    goalState->action = 0;

    /* crude way of skipping a line in c */
    c = getc(in);
    c = getc(in);
    while(c != '\n')
        c = getc(in);
    

    for(i = 0; i < size; ++i){
        if (fscanf(in, "%u", &ptr) != 1) {
            fprintf(stdout, "Failed to read\n");
            exit(-1);
        }
        startingState->state[i] = ptr;
    }

    /* crude way of skipping a line in c */
    c = getc(in);
    c = getc(in);
    while(c != '\n')
        c = getc(in);

    for(i = 0; i < size; ++i){
        if (fscanf(in, "%u", &ptr) != 1) {
            fprintf(stdout, "Failed to read\n");
            exit(-1);
        }
        goalState->state[i] = ptr;
    }

    world->goalState = goalState;
    world->goalState->key = hash(world, world->goalState);
    world->startingState = startingState;
    world->startingState->key = hash(world, world->startingState);

    world->puzzleVariant = 0; /*default*/
    fclose(in);

   return world;
}

