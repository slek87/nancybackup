#include "tiles.h"
#include "time.h"


struct Tiles* init_tiles(FILE *in){
    struct Tiles* tiles = malloc(sizeof(struct Tiles));
    readruml(tiles, in);
    initops(tiles);
    inithashvec(tiles);

    return tiles;
}

void free_tiles(struct Tiles* tiles){
    int i;
    for(i = 0; i < tiles->Ntiles; i++){
        free(tiles->hashvec[i]);
    }

    free(tiles->hashvec);
    free(tiles->init);
    free(tiles->goalpos);
    free(tiles->ops);
    free(tiles);
}

void readruml(struct Tiles *tiles, FILE *in) {
    unsigned int w, h;
    Tile t;
    unsigned int p;

    if (fscanf(in, " %u %u", &w, &h) != 2){
        fprintf(stdout, "Failed to read width and height");
        exit(-1);
    }

    tiles->Width = w;
    tiles->Height = h;
    tiles->Ntiles = w * h;
    tiles->ops = malloc(sizeof(struct Ops) * tiles->Ntiles);
    tiles->init = malloc(sizeof(unsigned int) * tiles->Ntiles);

    if (fscanf(in, " starting positions for each tile:") != 0){
        fprintf(stdout, "Failed to read the starting position label");
        exit(-1);
    }

    for (t = 0; t < tiles->Ntiles; t++) {
        int r = fscanf(in, " %u", &p);
        if (r != 1) {
            fprintf(stdout, "Failed to read the starting position for tile");
            exit(-1);
        }
        tiles->init[t] = p;
    }

    tiles->goalpos = malloc(sizeof(unsigned int) * tiles->Ntiles);

    if (fscanf(in, " goal positions:") != 0) {
        fprintf(stdout, "Failed to read the goal position label");
        exit(-1);
    }

    for (t = 0; t < tiles->Ntiles; t++) {
        if (fscanf(in, " %u", &p) != 1) {
            fprintf(stdout, "Failed to read the goal position");
            exit(-1);
        }
        tiles->goalpos[t] = p;
    }
}

void initops(struct Tiles* tiles) {
    unsigned int i;
    for (i = 0; i < tiles->Ntiles; i++) {
        tiles->ops[i].n = 0;
        if (i >= tiles->Width)
            tiles->ops[i].mvs[tiles->ops[i].n++] = i - tiles->Width;
        if (i % tiles->Width > 0)
            tiles->ops[i].mvs[tiles->ops[i].n++] = i - 1;
        if (i % tiles->Width < tiles->Width - 1)
            tiles->ops[i].mvs[tiles->ops[i].n++] = i + 1;
        if (i < tiles->Ntiles - tiles->Width)
            tiles->ops[i].mvs[tiles->ops[i].n++] = i + tiles->Width;
    }
}

void inithashvec(struct Tiles *tiles) {
    int i, j;
    tiles->hashvec = malloc(sizeof(unsigned long*) * tiles->Ntiles);
    srand(time(NULL));
    for (i = 0; i < tiles->Ntiles; i++) {
        tiles->hashvec[i] = malloc(sizeof(unsigned long) * tiles->Ntiles);
        for (j = 0; j < tiles->Ntiles; j++)
            tiles->hashvec[i][j] = rand();
    }
}

void dumptiles(struct Tiles *tiles, FILE *out, Tile ts[]) {
    unsigned int i;
    for (i = 0; i < tiles->Ntiles; i++) {
        if (i > 0 && i % tiles->Width == 0)
            fprintf(out, "\n");
        else if (i > 0)
            fprintf(out, "\t");
        fprintf(out, "%2d", ts[i]);
    }
    fprintf(out, "\n");
}

/*
static unsigned long hash(struct Tiles *tiles, Tile ts[], Pos b) {
    unsigned long h = 0;
    for (unsigned int i = 0; i < tiles->Ntiles; i++) {
        if (i == b)
            continue;
        h ^= hashvec[i][ts[i]];
    }
    return h;
}

static unsigned long korf_hash(struct Tiles *tiles, Tile ts[], Pos b) {
    unsigned long h = ts[0];
    for (int i = 1; i < tiles->Ntiles; i++)
        h += h * 3 + ts[i];
    return h;
}*/
