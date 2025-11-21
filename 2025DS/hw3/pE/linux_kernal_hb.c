#include <stdio.h>
#define u32 unsigned int
#define GOLDEN_RATIO_PRIME_32

typedef struct hlist_node {
    struct hlist_node *next, **pprev;
} hlist_node;

typedef struct list_head {
    struct hlist_node *first;
} list_head;

// initialize a hash table
hash_init 
// check whether a hashtable is empty
hash_empty 
// add an object to a hashtable
hash_add 
// remove an object from a hashtable
hash_del 
// iterate over a hashtable
hash_for_each 
//  iterate over all possible objects hashing to the same bucket
hash_for_each_possible 