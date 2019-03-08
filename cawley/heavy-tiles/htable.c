#include "htable.h"
#include "mdist.h"

struct htable* init_htable(int len){
    int i;
    struct htable *table = malloc(sizeof(struct htable));
    table->size = 0;
    table->len = len;

    table->arr = malloc(sizeof(struct hashentry*) * len);
    for(i = 0; i < len; i++){
        table->arr[i] = NULL;
    }

    return table;
}

static void rehash(struct htable* table){
    int i;
    struct hashentry *entry, *nxt;
    unsigned long ind;
    struct hashentry **new_arr = malloc(sizeof(struct hashentry*) * (table->len * 2));

    for(i = 0; i < table->len; i++){
        new_arr[i] = NULL;
    }

    for(i = 0; i < table->len; i++){
        entry = table->arr[i];
        while(entry != NULL){
            nxt = entry->next;
            ind = entry->hash % (table->len * 2);
            entry->next = new_arr[ind];
            new_arr[ind] = entry;
            entry = nxt;
        }
    }
    table->len *= 2;

    free(table->arr);
    table->arr = new_arr;
}


int add(struct htable* table, struct node* n, unsigned long hash){
    unsigned long ind = hash % table->len;

    struct hashentry* ent = malloc(sizeof(struct hashentry));
    ent->node = n;
    ent->hash = hash;
    ent->next = table->arr[ind];
    table->arr[ind] = ent;
    table->size++;

    /* Resize if necessary */
    if((float)table->size / table->len > 0.75){
        rehash(table);
    }


    return 1;
}

struct node* find(struct htable* table, struct mdist* mdist, struct state* s, unsigned long hash){
    unsigned long ind = hash % table->len;
    struct hashentry* cur;

    for(cur = table->arr[ind]; cur != NULL; cur = cur->next){
        if(equals(mdist, s, cur->node->state))
            return cur->node;
    }

    return NULL;
}

static void free_bucket(struct hashentry* h){
    if(h != NULL){
        free_bucket(h->next);
        free(h->node);
        free(h);
    }
}

void free_htable(struct htable* table){
    int i;
    for(i = 0; i < table->len; i++)
        free_bucket(table->arr[i]);

    free(table->arr);
    free(table);
}

