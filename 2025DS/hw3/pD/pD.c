#include "mst.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct PriorityQueue {
    Edge** Edges;
    int size;
    int capacity;
} PriorityQueue;

typedef struct HashSet {
    int* keys;
    char *used;
    int capacity;
    int size;
} HashSet;

static void offer(PriorityQueue* pq, Edge* e);
static Edge* poll(PriorityQueue* pq);
static inline bool pq_empty(const PriorityQueue* pq) { return pq->size == 0; }

static HashSet* hs_create(int cap_hint);
static HashSet* insert(HashSet* h, int key);
static bool containsKey(HashSet* h, int key);

// use prim algorithm since we do not know all the edges
void generate_mst(Node *start) {

    PriorityQueue* pq = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    pq->capacity = MAX_EDGES;
    pq->Edges = (Edge**) malloc(sizeof(Edge*) * pq->capacity);
    pq->size = 0;

    HashSet* seen = hs_create(100000);

    seen = insert(seen, start->id);
    for (int i = 0; i < start->edge_count; i++) {
        Edge* e = start->edges[i];
        if (containsKey(seen, e->v->id)) {
            offer(pq, e);
        }
    }
    
    while (seen->size < MAX_NODES && !pq_empty(pq)) {
        Edge* edge = poll(pq);
        if (edge == NULL) continue;

        Node* to = edge->v;
        if (containsKey(seen, to->id)) continue;

        edge->keep = 1;
        seen = insert(seen, to->id);

        for (int i = 0; i < to->edge_count; i++) {
            if (containsKey(seen, to->edges[i]->v->id) == false) {
                offer(pq, to->edges[i]);
                // Do not insert into seen when pushing candidates—only when an edge is accepted.
            }
        }
    }
};


static void offer(PriorityQueue* pq, Edge* e) {
    pq->size++;
}

static Edge* poll(PriorityQueue* pq) {
    pq->size--;
}

static inline unsigned hash_int(int x) { 
    unsigned h = (unsigned)x * 2654435761u; 
    h ^= h >> 16;
    return h;
}

static HashSet* hs_create(int cap_hint) {
    HashSet* h = (HashSet*) malloc(sizeof(HashSet));
    h->capacity = 1;
    while (h->capacity < cap_hint * 2) h->capacity << 1;// round up to power of two
    h->size = 0;
    h->keys = calloc(h->capacity, sizeof(int));
    h->used = calloc(h->capacity, sizeof(char));
}

static HashSet* insert(HashSet* h, int key) {

}

static bool containsKey(HashSet* h, int key) {

}