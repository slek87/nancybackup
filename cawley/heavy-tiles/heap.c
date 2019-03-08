#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "heap.h"

int size;
int length;



static unsigned int parent(unsigned int i){
    return (i - 1) / 2;
}

static unsigned int left(unsigned int i){
    return 2 * i + 1;
}

static int right(int i){
    return 2 * i + 2;
}

/*
 * i is the arr index of the first element
 * j is the arr index of the second element
 */
static void swap_heap_nodes(struct heap* min_heap, unsigned int i, unsigned int j){
    struct node* temp;
    min_heap->arr[i]->openind = j;
    min_heap->arr[j]->openind = i;

    temp = min_heap->arr[i];
    min_heap->arr[i] = min_heap->arr[j];
    min_heap->arr[j] = temp;
}

static void min_heapify(struct heap* min_heap, unsigned int index){
    unsigned int smallest = index;
    unsigned int l = left(index);
    unsigned int r = right(index);

    if(is_empty(min_heap))
        return;
    if(l <= min_heap->size && min_heap->arr[l]->state->d < min_heap->arr[index]->state->d){
        smallest = l;
    }
    if(r <= min_heap->size && min_heap->arr[r]->state->d < min_heap->arr[smallest]->state->d){
        smallest = r;
    }
    if(smallest != index){
        swap_heap_nodes(min_heap, index, smallest);
        min_heapify(min_heap, smallest);
    }
}

static void resize(struct heap* min_heap){
    min_heap->length *= 2;
    min_heap->arr = (struct node**) realloc(min_heap->arr, sizeof(struct node*) * min_heap->length);
}

struct node* heap_min(struct heap* min_heap){
    return min_heap->arr[0];
}

unsigned int is_empty(struct heap* min_heap) {
    if (min_heap->size == -1) {
        return 1;
    }
    return 0;
}

void heap_insert(struct heap* min_heap, struct node* n){
    min_heap->size++;
    if(min_heap->size == min_heap->length)
        resize(min_heap);
    n->openind = min_heap->size;
    min_heap->arr[min_heap->size] = n;
    heap_decrease_key(min_heap, min_heap->size);
}

int heap_contains(struct heap* min_heap, struct node* n){
    if(n->openind != -1)
        return 1;

    return 0;
}

void heap_decrease_key(struct heap* min_heap, unsigned int i){
    while(i > 0 && min_heap->arr[parent(i)]->state->d > min_heap->arr[i]->state->d){
        swap_heap_nodes(min_heap, parent(i), i);
        i = parent(i);
    }
}

struct node* heap_extract_min(struct heap* min_heap){
    struct node* min;
    min = min_heap->arr[0];
    min_heap->arr[0] = min_heap->arr[min_heap->size--];

    min_heapify(min_heap, 0);
    return min;
}


struct heap* init_heap(int len){
    struct heap* min_heap = (struct heap*) malloc(sizeof(struct heap));
    min_heap->size = -1;
    min_heap->length = len;
    min_heap->arr = malloc(sizeof(struct node*) * len);

    return min_heap;
}

void free_heap(struct heap* queue){
    free(queue->arr);
    free(queue);
}

