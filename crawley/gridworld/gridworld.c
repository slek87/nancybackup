//
// Created by doylew on 3/6/19.
//

#include "gridworld.h"
#include <string.h>

int successors(GridWorld* gridWorld, GridWorldState* state, GridWorldState* successors) {
    int num_successors = 0;
    int max_successors = 4;

    int current_x = state->agentLocation->x;
    int current_y = state->agentLocation->y;

    for (int i = 0; i < max_successors; ++i) {
        Location newLocation = {
                current_x + gridWorld->relativeLocation[i].x,
                current_y + gridWorld->relativeLocation[i].y
        };
        if (is_legal_location(gridWorld, &(newLocation))) {
            successors[num_successors].agentLocation = malloc(sizeof(Location));
            successors[num_successors].agentLocation->x = current_x + gridWorld->relativeLocation[i].x;
            successors[num_successors].agentLocation->y = current_y + gridWorld->relativeLocation[i].y;
            num_successors++;
        }
    }

    return num_successors;

}

double heuristic(GridWorld* gridWorld, GridWorldState* other) {
    // assuming unit costs
    return abs(gridWorld->targetLocation->x - other->agentLocation->x) +
            abs(gridWorld->targetLocation->y - other->agentLocation->y);
}

double distance(GridWorld* gridWorld, GridWorldState* other) {
    // assume unit costs
    return heuristic(gridWorld, other);
}

int equals(GridWorldState* state, GridWorldState* other) {
    if (other == NULL) {
        return false;
    } else if (state == other) {
        return true;
    } else {
        return state->agentLocation->x == other->agentLocation->x &&
                state->agentLocation->y == other->agentLocation->y;
    }
}

int hash(GridWorldState* state) {
    int x = state->agentLocation->x;
    int y = state->agentLocation->y;
    int shift = 16;
    // x XOR leftShift(y, 16)
    return x ^ ((y << shift) | (y >> (sizeof(y)*8 - shift)));
}

bool is_goal(GridWorld* gridWorld, GridWorldState* state) {
    return gridWorld->targetLocation->x == state->agentLocation->x &&
            gridWorld->targetLocation->y == state->agentLocation->y;
}

bool is_legal_location(GridWorld* gridWorld, Location* location) {
    bool is_legal = location->x >= 0 && location->y >= 0 && location->x < gridWorld->width &&
            location->y < gridWorld->height;
    bool not_blocked = true;
    for (int i = 0; i < gridWorld->height * gridWorld->width; ++i) {
        Location blockedCell = gridWorld->blockedCells[i];
        if (blockedCell.x == -1 && blockedCell.y == -1) {
            break;
        }
        if (location->x == blockedCell.x && location->y == blockedCell.y) {
            not_blocked = false;
            break;
        }
    }
    return is_legal && not_blocked;
}

void free_gridworld(GridWorld* gridWorld) {
    free(gridWorld->blockedCells);
    free(gridWorld->startLocation);
    free(gridWorld->relativeLocation);
    free(gridWorld->targetLocation);
    free(gridWorld);
}

GridWorld* init_gridworld(FILE *in) {
    GridWorld* gridWorld = malloc(sizeof(GridWorld));

    unsigned int width, height;
    GridWorld gw;

    if (fscanf(in, "%u\n%u\n", &width, &height) != 2) {
        fprintf(stdout, "Failed to read width and height\n");
        exit(-1);
    }

    fprintf(stdout, "%u\n%u\n", width, height);

    gridWorld->width = width;
    gridWorld->height = height;
    gridWorld->relativeLocation = malloc(sizeof(Location) * 4);
    Location left = {-1, 0};
    Location down = {0, 1};
    Location up = {0, -1};
    Location right = {1, 0};
    gridWorld->relativeLocation[0] = left;
    gridWorld->relativeLocation[1] = down;
    gridWorld->relativeLocation[2] = up;
    gridWorld->relativeLocation[3] = right;

    gridWorld->startLocation = malloc(sizeof(Location));
    gridWorld->blockedCells = malloc(sizeof(Location) * (width * height));

    int b;
    for (b = 0; b < height * width; ++b) {
        gridWorld->blockedCells[b].x = -1;
        gridWorld->blockedCells[b].y = -1;
    }

    gridWorld->targetLocation = malloc(sizeof(Location));

    int numCellsBlocked = 0;
    int i;
    int j;
    char line[width];
    for (i = 0; i < height; ++i) {
        int scan = fscanf(in, "%s\n", line);
        if (scan != 1) {
            fprintf(stdout, "Failed to read line (%s)[%d] from file, check width\n", line, scan);
            exit(-1);
        }
        fprintf(stdout, "%s\n", line);
        for (j = 0; j < width; ++j) {
            char c = line[j];
            if (c == '#') {
                gridWorld->blockedCells[numCellsBlocked].x = i;
                gridWorld->blockedCells[numCellsBlocked].y = j;
                numCellsBlocked++;
            } else if (c == '@') {
                gridWorld->startLocation->x = i;
                gridWorld->startLocation->y = j;
            } else if (c == '*') {
                gridWorld->targetLocation->x = i;
                gridWorld->targetLocation->y = j;
            } else {
                // do nothing
            }
        }
    }

    return gridWorld;
}

