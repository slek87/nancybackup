#ifndef HEADER_FILE
#define HEADER_FILE

#include "node.h"

struct heap* init_heap(int len);

struct node* heap_min(struct heap*);
struct node* heap_extract_min(struct heap* queue);
void heap_insert(struct heap*, struct node*);
int heap_contains(struct heap*, struct node*);
unsigned int is_empty(struct heap* queue);
void heap_decrease_key(struct heap* queue, unsigned int i);
void free_heap(struct heap* queue);

struct heap_node {
    /* Point to this heap_node's corresponding node */
    unsigned int node_index;
};

struct heap {
    /* Current length of the underlying array of the heap */
    unsigned int length;

    /* Current number of elements in the heap */
    unsigned int size;

    /* Pointer to the underlying array for this heap. */
    struct node** arr;
};

#endif
