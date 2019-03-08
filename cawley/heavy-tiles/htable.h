
#ifndef SLIDING_TILES_HTABLE_H
#define SLIDING_TILES_HTABLE_H

#include "node.h"
#include "mdist.h"

struct htable{
    struct hashentry** arr;
    unsigned int size;
    unsigned int len;
};

struct hashentry{
    struct hashentry* next;
    struct node* node;
    unsigned long hash;
};


struct htable* init_htable(int size);
int add(struct htable* table, struct node* n, unsigned long hash);
struct node* find(struct htable* table, struct mdist* m, struct state* s, unsigned long hash);
void free_htable(struct htable* table);


#endif
