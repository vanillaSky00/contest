#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

#define HASH_EMPTY 0
#define HASH_OCCUPIED 1
#define HASH_CAP 20011  // a prime > 2×max n to reduce collisions

typedef struct Entry {
    int key;
    int val;
    char used;
} Entry;

typedef struct HashMap {
    Entry table[HASH_CAP];
    int size;
} HashMap;

HashMap hs = {0};

static inline uint32_t hash_int(int key) {
    uint32_t h = (uint32_t)key * 2654435761u;  // Knuth’s multiplicative hash
    return h % HASH_CAP;
}

static int quadratic_probing() {

}

static int linear_probing(int key) {
    uint32_t i = hash_int(key);
    while (hs.table[i].used == HASH_OCCUPIED) {
        i = (i + 1) % HASH_CAP;
    } 
    return i;
}

static int find_slot(int key) {
    return linear_probing(key);
}

void insert(Data *data) {
    unsigned idx = find_slot(data->key);
    hs.table[idx].key = data->key;
    hs.table[idx].val = data->value;
    hs.table[idx].used = HASH_OCCUPIED;
}

void remove(int key) {
    unsigned idx = find_slot(key);
    hs.table[idx].used = HASH_EMPTY;
}

int search(int key) {
    unsigned idx = find_slot(key);
    return (hs.table[idx].key == key && hs.table[idx].used == HASH_OCCUPIED) ? hs.table[idx].val : -1;
}

