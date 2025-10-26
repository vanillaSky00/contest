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


static inline int compare_edge(Edge* e1, Edge* e2) {
    if (e1->w > e2->w) return 1; // might stackoverflow if we return w1 - w2
    else if (e1->w < e2->w) return -1;
    else return 0;
}

static inline void swap_edges(Edge** x, Edge** y) {
    Edge* tmp = *x; 
    *y = tmp;
    *x = tmp;
}

static void heapify_up(PriorityQueue* pq, int idx) {
    if (pq == NULL || idx < 0 || idx >= pq->size) return;

    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (compare_edge(pq->Edges[idx], pq->Edges[parent]) < 0) {
            swap_edges(&pq->Edges[idx], &pq->Edges[parent]);
            idx = idx / 2;
        }
        else break;
    }
}

static void heapify_down(PriorityQueue* pq, int idx) {
    if (pq == NULL || idx < 0 || idx >= pq->size) return;

    while (true) {
        int least = idx;
        int left = idx * 2 + 1; 
        int right = idx * 2 + 2;

        if (left < pq->size && compare_edge(pq->Edges[left], pq->Edges[least]) < 0) least = left;
        if (right < pq->size && compare_edge(pq->Edges[right], pq->Edges[least]) < 0) least = right;
        
        if (least == idx) break;
        swap_edges(&pq->Edges[least], &pq->Edges[idx]);
        idx = least;
    }
}

static void offer(PriorityQueue* pq, Edge* e) {
    if (pq == NULL || e == NULL) return;

    if (pq->size == pq->capacity) {
        int newcap = pq->capacity ? pq->capacity * 2 : 16;
        pq->Edges = realloc(pq->Edges, sizeof(Edge*) * newcap);
        pq->capacity = newcap;
    }

    pq->Edges[pq->size] = e;
    pq->size++;
    heapify_up(pq, pq->size - 1);
}

static Edge* poll(PriorityQueue* pq) {
    if (pq == NULL || pq->size <= 0) return NULL;
    Edge* min = pq->Edges[0];
    pq->size--;

    if (pq->size > 0) {
        pq->Edges[0] = pq->Edges[pq->size];
        heapify_down(pq, 0);
    }

    return min;
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