

#ifndef SLIDING_TILES_ASTAR_H
#define SLIDING_TILES_ASTAR_H

#include "mdist.h"
#include "node.h"
#include "htable.h"
#include "heap.h"
#include "system.h"

struct search{
    struct htable* closedlist;
    struct heap* openlist;
    struct mdist* mdist;
};

#endif
