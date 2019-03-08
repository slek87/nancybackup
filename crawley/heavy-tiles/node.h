
#ifndef SLIDING_TILES_NODE_H
#define SLIDING_TILES_NODE_H

#include "mdist.h"

struct node{
    int g;
    struct node* parent;
    struct state* state;
    int op;
    int pop;
    int openind;
    int f;
};

struct node* initial_node(struct state* s);
struct node* make_node(struct state* s);
void free_node(struct node * n);

#endif
