#include "node.h"

#include <stdlib.h>

struct node* initial_node(struct state* s){
    struct node* initial = (struct node*) malloc(sizeof(struct node));
    initial->state = s;
    initial->g = 0;
    initial->parent = NULL;
    initial->openind = 0;
    initial->f = h(s);
    initial->pop = -1;
    initial->op = -1;

    return initial;
}

struct node* make_node(struct state* s){
    struct node* new_node = malloc(sizeof(struct node));
    new_node->parent = NULL;
    new_node->g = 0;
    new_node->state = s;

    return new_node;
}

void free_node(struct node* n){
    free_state(n->state);
    free(n);
}