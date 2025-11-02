#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define HASH_EMPTY 0
#define HASH_OCCUPIED 1
#define HASH_DELETED 2
#define HASH_CAP 20011  // a prime > 2×max n to reduce collisions

typedef struct Entry {
    int key;
    int val;
    unsigned char state;
} Entry;

typedef struct HashMap {
    Entry table[HASH_CAP];
    int size;
} HashMap;

HashMap hs = {0};

static inline uint32_t hash_int(int key) {
    return (uint32_t)key * 2654435761u % HASH_CAP;  // Knuth’s multiplicative hash
}

static int find_index(int key) {
    uint32_t i = hash_int(key);
    uint32_t start = i;
    while(true) {
        unsigned char state = hs.table[i].state;
        if (state == HASH_EMPTY) return -1;
        if (state == HASH_OCCUPIED && hs.table[i].key == key) return i;
        i = (i + 1) % HASH_CAP;
        if (i == start) return -1;
    }
}

// return -1 if table is full
static int find_insert_slot(int key) {
    uint32_t i = hash_int(key);
    uint32_t start = i;
    int first_deleted = -1;
    while (true) {
        unsigned char state = hs.table[i].state;
        if (state == HASH_EMPTY) {
            return (first_deleted != -1) ? first_deleted : (int)i;
        }
        else if (state == HASH_OCCUPIED) {
            if (hs.table[i].key == key) return (int)i;
        }
        else {
            if (first_deleted == -1) first_deleted = (int)i;
        }
        i = (i + 1) % HASH_CAP;
        if (i == start) return first_deleted;
    }
}

void insert(Data *data) {
    int idx = find_insert_slot(data->key);
    if (idx < 0) {
        // full, rehash
        return;
    }

    if (hs.table[idx].state == HASH_OCCUPIED) {
        hs.table[idx].val = data->value;
        return;
    }

    hs.table[idx].key = data->key;
    hs.table[idx].val = data->value;
    hs.table[idx].state = HASH_OCCUPIED;
    hs.size++;
}

int search(int key) {
    int idx = find_index(key);
    return (idx >= 0 && hs.table[idx].key == key && hs.table[idx].state == HASH_OCCUPIED) ? hs.table[idx].val : -1;
}

void remove(int key) {
    int idx = find_index(key);
    if (idx >= 0) {
        hs.table[idx].state = HASH_DELETED;
        hs.size--;
    }
}