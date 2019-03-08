#include "astar.h"

int gen = 0;

static struct search* init_search(struct mdist* mdist){
    struct search* search = malloc(sizeof(struct search));

    search->closedlist = init_htable(10);
    search->openlist = init_heap(10);
    search->mdist = mdist;

    return search;
}

void free_search(struct search *s){
    free_heap(s->openlist);
    free_htable(s->closedlist);
    free_mdist(s->mdist);
    free(s);
}

void considerkid(struct search* search, struct node* parent, struct state* state, Oper op){
    unsigned long hash;
    struct node* dup;
    int isopen;

    struct edge* e = make_edge(search->mdist, state, op);
    struct node* kid = make_node(e->state);
    kid->g = parent->g + e->cost;

    hash = get_hash(search->mdist, kid->state);
    dup = find(search->closedlist, search->mdist, kid->state, hash);

    if(dup != NULL){
        if(kid->g >= dup->g){
            free_node(kid);
            free_edge(e);
            return;
        }
        isopen = heap_contains(search->openlist, dup);

        dup->f = dup->f - dup->g + kid->g;
        dup->g = kid->g;
        dup->parent = parent;
        dup->op = op;
        dup->pop = e->revop;

        if(isopen)
            heap_decrease_key(search->openlist, dup->openind);
        else
            heap_insert(search->openlist, dup);

        free_node(kid);
        free_edge(e);
    }
    else{
        kid->f = kid->g + h(e->state);
        kid->parent = parent;
        kid->op = op;
        kid->pop = e->revop;
        add(search->closedlist, kid, hash);
        heap_insert(search->openlist, kid);

        free_edge(e);
    }
}

static void expand(struct search* search, struct node* n){
    unsigned int i;
    struct operators* ops = make_operators(search->mdist, n->state);
    for(i = 0; i < ops->n; i++){
        if(ops->mvs[i] == n->pop)
            continue;
        gen++;
        considerkid(search, n, n->state, ops->mvs[i]);
    }

    free_operators(ops);
}

/*static void printpath(struct search* search, struct node* n){
    if(n->parent == NULL) {
        dumpstate(search->mdist, n->state);
    }
    else {
        printpath(search, n->parent);
        dumpstate(search->mdist, n->state);
    }

    printf("\n");
}*/

int astar(struct mdist* mdist, struct state* start){
    struct node* cur;
    struct search* search = init_search(mdist);

    struct node* initial = initial_node(start);
    add(search->closedlist, initial, get_hash(search->mdist, start));
    heap_insert(search->openlist, initial);

    while(!is_empty(search->openlist)){
        cur = heap_extract_min(search->openlist);

        if(isgoal(cur->state)){
/*
            printpath(search, cur);
*/
            printf("cost: %d\n", cur->g);
            break;
        }

        expand(search, cur);
    }


    free_search(search);

    return 0;
}


int main(int argc, char* argv[]){
    int ret;
    double start, end;
    struct mdist* mdist = make_mdist(stdin);

    struct state* init = initial_state(mdist);
    start = get_current_seconds();

    ret = astar(mdist, init);
    if(ret != 0)
        printf("Path not found!\n");

    end = get_current_seconds();
    printf("nodes generated: %d\n", gen);
    printf("time: %f seconds\n", end-start);

    return 0;
}

