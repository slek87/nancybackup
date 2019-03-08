#include "mdist.h"

static void initmd(struct mdist *mdist){
    unsigned int t;
    int i, row, col, r, c;

    for (t = 1; t < mdist->tiles->Ntiles; t++) {
        row = mdist->tiles->goalpos[t] / mdist->tiles->Width;
        col = mdist->tiles->goalpos[t] % mdist->tiles->Width;
        for (i = 0; i < mdist->tiles->Ntiles; i++) {
            r = i / mdist->tiles->Width;
            c = i % mdist->tiles->Width;

            /* Changed this to be t * ... */
            mdist->md[t][i] = t * (abs(r - row) + abs(c - col));
        }
    }
}

static void initincr(struct mdist *mdist){
    unsigned int t, nw, next, n, old;

    for (t = 1; t < mdist->tiles->Ntiles; t++) {
        for (nw = 0; nw < mdist->tiles->Ntiles; nw++) {
            next = mdist->md[t][nw];
            for (n = 0; n < mdist->tiles->ops[nw].n; n++) {
                old = mdist->tiles->ops[nw].mvs[n];
                mdist->incr[t][nw][old] = mdist->md[t][old] - next;
                mdist->incrd[t][nw][old] = (mdist->md[t][old] - next) / t;
            }
        }
    }
}

struct mdist* make_mdist(FILE* file){
    struct Tiles* tiles = init_tiles(file);
    struct mdist* mdist = malloc(sizeof(struct mdist));
    int i, j;

    mdist->tiles = tiles;
    mdist->md = malloc(sizeof(unsigned int*) * tiles->Ntiles);
    mdist->incr = malloc(sizeof(int**) * tiles->Ntiles);
    mdist->incrd = malloc(sizeof(int**) * tiles->Ntiles);
    for(i = 0; i < tiles->Ntiles; i++){
        mdist->md[i] = malloc(sizeof(unsigned int) * tiles->Ntiles);
        mdist->incr[i] = malloc(sizeof(int*) * tiles->Ntiles);
        mdist->incrd[i] = malloc(sizeof(int*) * tiles->Ntiles);
        for(j = 0; j < tiles->Ntiles; j++){
            mdist->incr[i][j] = malloc(sizeof(int) * tiles->Ntiles);
            mdist->incrd[i][j] = malloc(sizeof(int) * tiles->Ntiles);
        }
    }

    initmd(mdist);
    initincr(mdist);

    return mdist;
}

void free_mdist(struct mdist* mdist){
    int i, j;

    for(i = 0; i < mdist->tiles->Ntiles; i++){
        free(mdist->md[i]);
        for(j = 0; j < mdist->tiles->Ntiles; j++){
            free(mdist->incr[i][j]);
        }
        free(mdist->incr[i]);
    }

    free_tiles(mdist->tiles);
    free(mdist->md);
    free(mdist->incr);
    free(mdist);
}

struct state* initial_state(struct mdist *mdist){
    int i;
    struct state* init_state = malloc(sizeof(struct state));
    init_state->h = 0;
    init_state->d = 0;

    init_state->tiles = malloc(sizeof(Tile) * mdist->tiles->Ntiles);
    for (i = 0; i < mdist->tiles->Ntiles; i++) {
        if (mdist->tiles->init[i] == 0)
            init_state->b = i;
        else{
            init_state->h += mdist->md[mdist->tiles->init[i]][i];
            init_state->d += (mdist->md[mdist->tiles->init[i]][i] / mdist->tiles->init[i]);
        }

        init_state->tiles[i] = mdist->tiles->init[i];
    }

    return init_state;
}

Cost h(struct state* s){
    return s->h;
}

Cost d(struct state* s){
    return s->d;
}

int isgoal(struct state* s){
    return s->h == 0;
}

void dumpstate(struct mdist* mdist, struct state* s){
    s->tiles[s->b] = 0;
    dumptiles(mdist->tiles, stdout, s->tiles);
}

int equals(struct mdist* mdist, struct state* s1, struct state* s2){
    unsigned int i;

    if (s1->b != s2->b)
        return 0;
    for (i = 0; i < mdist->tiles->Ntiles; i++) {
        if (s1->tiles[i] != s2->tiles[i] && i != s1->b)
            return 0;
    }

    return 1;
}

struct operators* make_operators(struct mdist* mdist, struct state* s){
    struct operators* ops = malloc(sizeof(struct operators));
    ops->n = mdist->tiles->ops[s->b].n;
    ops->mvs = mdist->tiles->ops[s->b].mvs;

    return ops;
}

void free_operators(struct operators* ops){
    free(ops);
}

static unsigned long korf_hash(struct Tiles *tiles, Tile ts[]) {
    int i;
    unsigned long h = ts[0];
    for (i = 1; i < tiles->Ntiles; i++)
        h += h * 3 + ts[i];
    return h;
}

unsigned long get_hash(struct mdist* mdist, struct state* s){
    return korf_hash(mdist->tiles, s->tiles);
}

struct edge* make_edge(struct mdist* mdist, struct state* s, Oper op){
    Tile t;
    struct edge* e = malloc(sizeof(struct edge));
    e->cost = s->tiles[op];
    e->revop = s->b;
    e->revcost = s->tiles[op];

    e->state = make_state(mdist, s->tiles);
    e->state->h = s->h;
    e->state->d = s->d;

    t = s->tiles[op];
    e->state->tiles[s->b] = t;
    e->state->h += mdist->incr[t][op][s->b];
    e->state->d += mdist->incrd[t][op][s->b];
    e->state->b = op;

    return e;
}

void free_edge(struct edge* e){
    free(e);
}

struct state* make_state(struct mdist* mdist, Tile* t){
    unsigned int i;
    struct state* new_state = malloc(sizeof(struct state));
    new_state->tiles = malloc(sizeof(Tile) * mdist->tiles->Ntiles);

    for (i = 0; i < mdist->tiles->Ntiles; i++) {
        new_state->tiles[i] = t[i];
    }

    return new_state;
}

void free_state(struct state* s){
    free(s->tiles);
    free(s);
}


