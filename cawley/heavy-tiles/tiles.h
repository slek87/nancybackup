#ifndef SLIDING_TILES_TILES_H
#define SLIDING_TILES_TILES_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int Tile;
typedef unsigned int Pos;

typedef int Cost;
typedef int Oper;

struct Ops{
    unsigned int n;
    Pos mvs[4];
};

struct Tiles{
    int Ntiles;
    int Width;
    int Height;
    unsigned long** hashvec;
    Tile* init;
    Pos* goalpos;
    struct Ops* ops;
};


struct Tiles* init_tiles(FILE *);
void readruml(struct Tiles *tiles, FILE *in);
void initops(struct Tiles *tiles);
void dumptiles(struct Tiles *tiles, FILE *out, Tile ts[]);
void inithashvec(struct Tiles *tiles);
void free_tiles(struct Tiles *tiles);



#endif
