
#ifndef SLIDING_TILES_MDIST_H
#define SLIDING_TILES_MDIST_H

#include "tiles.h"

struct mdist{
    struct Tiles* tiles;
    unsigned int **md;
    int ***incr;
    int ***incrd;
};

struct state{
    Tile *tiles;
    Pos b;
    Cost h;
    Cost d;
};

struct operators{
    unsigned int n;
    const Pos *mvs;
};

struct edge{
    Cost cost;
    Oper  revop;
    Cost revcost;
    struct state* state;
};

struct state* initial_state(struct mdist* m);
struct mdist* make_mdist(FILE* file);
struct edge* make_edge(struct mdist* mdist, struct state* s, Oper op);
struct state* make_state(struct mdist* mdist, Tile* t);
struct operators* make_operators(struct mdist* m, struct state* s);

Cost h(struct state* s);
Cost d(struct state* s);
int isgoal(struct state* s);
void dumpstate(struct mdist* mdist, struct state* s);
int equals(struct mdist* mdist, struct state* s1, struct state* s2);
unsigned long get_hash(struct mdist* mdist, struct state* s);

void free_state(struct state* s);
void free_operators(struct operators* ops);
void free_edge(struct edge* e);
void free_mdist(struct mdist* mdist);


#endif
