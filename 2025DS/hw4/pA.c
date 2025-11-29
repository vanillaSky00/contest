#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define NODE_CAP 10001
typedef struct Node {
    int key;
    int mark; 
    int degree;
    struct Node *next;
    struct Node *child_head;
} Node;

typedef struct Fheap {
    Node *root;
    int min;
} Fheap;

Node *handler[NODE_CAP];

void free_node(Node *n) {
    if (n) free(n);
}

void free_fheap() {

}

Node *create_node(int key) {
    Node *n = (Node*) calloc(1, sizeof(Node));
    if (!n) perror("create_node");
    n->key = key;
    return n;
}

Fheap *init_fheap() {
    Fheap *f = (Fheap *) malloc(sizeof(Fheap));
    
    Node *dummy_head = (Node *) create_node(INT32_MIN); 
    Node *dummy_tail = (Node *) create_node(INT32_MIN);
    dummy_head->degree = dummy_tail->degree = -1;

    f->root = dummy_head;
    dummy_head->next = dummy_tail;
    return f;
}



void consolidate(Node *n) {

}

void cuscading_cut() {

}

void insert(Fheap *f, int key) {
    // O(1) lazy 
    Node *new_node = create_node(key);
    handler[key] = new_node;
    
    new_node->next = f->root->next;
    f->root->next = new_node;
}

void delete(Fheap *f, int key) {
    printf("delete %d\n", key);
}

void decrease(Fheap *f, int key, int val) {
    printf("decrease %d %d\n", key, val);
}

int extract_min(Fheap *f) {
    int min = f->min;
    delete(f, min);
    //printf("extract-min\n");
    return min;
}

void test_print(Fheap *f) {
    Node *curr = f->root;

    while (curr != NULL) {
        printf("key: %d, mark: %d, degree: %d\n", curr->key, curr->mark, curr->degree);
        curr = curr->next;
    }
}

#define MAX_BUFF 12
int main(void) {

    char *cmd = malloc(MAX_BUFF);
    int key;
    int val;
    Fheap* fheap = init_fheap();

    while (true) {
        if (scanf("%11s", cmd) != 1)   // safe input
            break;

        if (strcmp(cmd, "insert") == 0) {
            scanf("%d", &key);
            insert(fheap, key);
        } 
        else if (strcmp(cmd, "delete") == 0) {
            scanf("%d", &key);
            delete(fheap, key);
        }
        else if (strcmp(cmd, "decrease") == 0) {
            scanf("%d", &key);
            scanf("%d", &val);
            decrease(fheap, key, val);
        }
        else if (strcmp(cmd, "extract-min") == 0) {
            extract_min(fheap);
        }
        else if (strcmp(cmd, "exit") == 0) {
            test_print(fheap);
            free(cmd);
            return 0;
        }
        else {
            fprintf(stderr, "Invalid arguments\n");
            return -1;
        }
    }
}