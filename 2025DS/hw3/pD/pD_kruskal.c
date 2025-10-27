#include "mst.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define HASH_EMPTY 0
#define HASH_OCCUPIED 1

//#define DEBUG_LOG(msg,...)
#define DEBUG_LOG(msg,...) printf("Debug: " msg "\n" , ##__VA_ARGS__)

typedef struct HashSet {
    int* keys;
    char* used;
    int capacity;
    int size;
} HashSet;

typedef struct DSU {
    int* parent;
    int* rank;
} DSU;

static int find(DSU* dsu, int x);
static void unionFind(DSU* dsu, int x, int y);
static inline int compare_edge(const void* e1, const void* e2);

static HashSet* hs_create(int cap_hint);
static void hs_add(HashSet* h, int key);
static bool containsKey(HashSet* h, int key);

static Edge** bfs(Node *start, int* n, int* e); // find number of nodes first

// be careful that edge is undirected so u or v should be considered
static inline Node* other(const Edge* e, const Node* from) {
    if (e->u == from) return e->v;
    if (e->v == from) return e->u;
    return NULL; // will not happend
}


// use prim algorithm since we do not know all the edges
void generate_mst(Node *start) {
    int node_size, edge_count;
    Edge** edges = bfs(start, &node_size, &edge_count);
    DEBUG_LOG("node_size = %d, edge_count = %d", node_size, edge_count);

    DSU* dsu = (DSU*) malloc(sizeof(DSU));
    dsu->parent = (int*) malloc(sizeof(int) * node_size);
    dsu->rank = (int*) calloc(node_size, sizeof(int));
    for (int i = 0; i < node_size; i++) {
        dsu->parent[i] = i;
    }

    qsort(edges, edge_count, sizeof(Edge*), compare_edge);

    //check if cycle
    int res_count = 0;
    
    DEBUG_LOG("after qsort");
    for (int i = 0; i < edge_count; i++) {
        DEBUG_LOG("w: %d", edges[i]->w);
        int u = edges[i]->u->id;
        int v = edges[i]->v->id;
        
        if (find(dsu, u) == find(dsu, v)) continue;
        unionFind(dsu, u, v);
        edges[i]->keep = 1;
        res_count++;
        if (res_count == node_size - 1) break;
    }
};

static inline int compare_edge(const void* a, const void* b) {
    const Edge* e1 = *(Edge* const*)a;
    const Edge* e2 = *(Edge* const*)b;
    // avoid overflow from subtraction
    if (e1->w < e2->w) return -1;
    if (e1->w > e2->w) return 1;
    return 0;
}

static Edge** bfs(Node* start, int* n, int* e) {
    if (!start) return 0;

    HashSet* seen = hs_create(MAX_NODES);
    Node** q = (Node**) malloc(sizeof(Node*) * MAX_NODES);
    Edge** edges = (Edge**) malloc(sizeof(Edge*) * MAX_EDGES);

    int front = 0, rear = 0;
    int node_size = 0, edge_count = 0;

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
                edges[edge_count++] = at->edges[i];
            }
        }
    }

    free(seen);
    free(q);
    *n = node_size;
    *e = edge_count;
    return edges;
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

static int find(DSU* dsu, int x) {
    return (dsu->parent[x] == x) ? x : (dsu->parent[x] = find(dsu, dsu->parent[x]));
}

static void unionFind(DSU* dsu, int x, int y) {
    x = find(dsu, x);
    y = find(dsu, y);
    if (x == y) return;
    if (dsu->rank[x] > dsu->rank[y]) dsu->parent[y] = x;
    else if (dsu->rank[y] > dsu->rank[x]) dsu->parent[x] = y;
    else {
        dsu->parent[x] = y;
        dsu->rank[y]++;
    }
}