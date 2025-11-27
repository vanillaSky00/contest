#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int key;
    int mark; 
    int degree;
    struct Node *next;
    struct Node *child_head;
} Node;

typedef struct Fheap {
    Node *next;
    int min;
} Fheap;

void free_node(Node *n) {
    if (n) free(n);
}

Node *create_node(int key) {
    Node *n = (Node*) malloc(sizeof(Node));
    n->key = key;
    n->mark = 0;
    n->degree = 0;
    n->next = NULL;
    n->child_head = NULL;
}

void insert(Fheap *f, int key) {
    Node *node = create_node(key);
    
    if (f->next == NULL) f->next = node;
    node->next = f->next;
    f->next = node;
    printf("insert %d\n", key);
}

void delete(Fheap *f, int key) {
    printf("delete %d\n", key);
}

void decrease(Fheap *f, int key, int val) {
    printf("decrease %d %d\n", key, val);
}

int extract_min(Fheap *f) {
    printf("extract-min\n");
    return 0;
}

#define MAX_BUFF 12
int main(void) {

    char *cmd = malloc(MAX_BUFF);
    int key;
    int val;
    Fheap* fheap = (Fheap*) malloc(sizeof(Fheap));

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
            return 0;
        }
        else {
            fprintf(stderr, "Invalid arguments\n");
            return -1;
        }
    }

    free(cmd);
    return 0;
}