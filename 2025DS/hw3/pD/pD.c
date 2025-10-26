#include "mst.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define HASH_EMPTY 0
#define HASH_OCCUPIED 1

#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("Debug: " msg "\n" , ##__VA_ARGS__)

typedef struct PriorityQueue {
    Edge** Edges;
    int size;
    int capacity;
} PriorityQueue;

typedef struct HashSet {
    int* keys;
    char* used;
    int capacity;
    int size;
} HashSet;

static void offer(PriorityQueue* pq, Edge* e);
static Edge* poll(PriorityQueue* pq);
static inline bool pq_empty(const PriorityQueue* pq) { return pq->size == 0; }

static HashSet* hs_create(int cap_hint);
static void hs_add(HashSet* h, int key);
static bool containsKey(HashSet* h, int key);

static int bfs(Node *start); // find number of nodes first

// be careful that edge is undirected so u or v should be considered
static inline Node* other(const Edge* e, const Node* from) {
    if (e->u == from) return e->v;
    if (e->v == from) return e->u;
    return NULL; // will not happend
}


// use prim algorithm since we do not know all the edges
void generate_mst(Node *start) {
    PriorityQueue* pq = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    pq->capacity = MAX_EDGES;
    pq->Edges = (Edge**) malloc(sizeof(Edge*) * pq->capacity);
    pq->size = 0;

    HashSet* seen = hs_create(MAX_NODES);

    hs_add(seen, start->id);
    for (int i = 0; i < start->edge_count; i++) {
        Edge* e = start->edges[i];
        if (!containsKey(seen, other(e, start)->id)) { 
            offer(pq, e);
        }

    }
    
    int node_size = bfs(start);
    DEBUG_LOG("node_size = %d", node_size);

    while (seen->size < node_size && !pq_empty(pq)) {
        DEBUG_LOG("in pq");
        Edge* edge = poll(pq);
        if (edge == NULL) continue;

        // Determine which side is the new vertex across the cut
        bool u_seen = containsKey(seen, edge->u->id);
        bool v_seen = containsKey(seen, edge->v->id);
        
        Node* to = NULL;
        if (u_seen && !v_seen) to = edge->v;
        else if (v_seen && !u_seen) to = edge->u;
        else continue;

        edge->keep = 1;
        hs_add(seen, to->id);

        for (int i = 0; i < to->edge_count; i++) {
            if (!containsKey(seen, other(to->edges[i], to)->id)) {
                offer(pq, to->edges[i]);
                // Do not insert into seen when pushing candidates—only when an edge is accepted.
            }
        }
    }

    free(pq->Edges);
    free(pq);
    free(seen->keys);
    free(seen->used);
    free(seen);
};

static inline int compare_edge(Edge* e1, Edge* e2) {
    if (e1->w > e2->w) return 1; // might stackoverflow if we return w1 - w2
    else if (e1->w < e2->w) return -1;
    else return 0;
}

static inline void swap_edges(Edge** x, Edge** y) {
    Edge* tmp = *x; 
    *x = *y;
    *y = tmp;
}

static void heapify_up(PriorityQueue* pq, int idx) {
    if (pq == NULL || idx < 0 || idx >= pq->size) return;

    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (compare_edge(pq->Edges[idx], pq->Edges[parent]) < 0) {
            swap_edges(&pq->Edges[idx], &pq->Edges[parent]);
            idx = parent;
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
    while (h->capacity < cap_hint * 2) h->capacity <<= 1;// round up to power of two

    h->size = 0;
    h->keys = (int*) calloc(h->capacity, sizeof(int));
    h->used = (char*) calloc(h->capacity, sizeof(char));
    return h;
}

static inline unsigned linear_probing(HashSet* h, int key) {
    int i = hash_int(key) & (unsigned)(h->capacity - 1); // capacity must be a power of two

    while (h->used[i]) {
        if (h->keys[i] == key) return i;
        i = (i + 1u) & (unsigned)(h->capacity - 1);
    }
    return i;
}

static void hs_add(HashSet* h, int key) {
    if (h == NULL) return;

    if ((float)h->size / h->capacity > 0.7f) {
        // Optional: implement rehash if needed; skip for 100k static use
    }

    unsigned idx = linear_probing(h, key);
    if (h->used[idx]) return;

    h->used[idx] = HASH_OCCUPIED;
    h->keys[idx] = key;
    h->size++;
}

static bool containsKey(HashSet* h, int key) {
    if (h == NULL) return false;

    unsigned idx = linear_probing(h, key);
    return h->used[idx] && (h->keys[idx] == key);
}

static int bfs(Node* start) {
    if (!start) return 0;

    HashSet* seen = hs_create(MAX_NODES);
    Node** q = (Node**) malloc(sizeof(Node*) * MAX_NODES);
    int front = 0, rear = 0;
    int node_size = 0;

    hs_add(seen, start->id);
    q[rear++] = start;
    node_size++;

    while (rear > front) {
        Node* at = q[front++];
        
        for (int i = 0; i < at->edge_count; i++) {
            Node* o = other(at->edges[i], at);
            if (!containsKey(seen, o->id)) {
                hs_add(seen, o->id);  
                q[rear++] = o;
                node_size++;
            }
        }
    }

    free(seen);
    free(q);
    return node_size;
}