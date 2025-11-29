#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define NODE_CAP 10001
#define MAX_DEGREE 500
typedef struct Node {
    int key;
    int mark; 
    int degree;
    struct Node *next;
    struct Node *prev;
    struct Node *parent;
    struct Node *child_head;
} Node;

typedef struct Fheap {
    Node *root;
    int min;
} Fheap;

Node *handler[NODE_CAP];
Node *degrees[MAX_DEGREE];

void free_node(Node *n);
void free_fheap();
Node *create_node(int key);
Fheap *init_fheap();
Node *unite(Node *tree1, Node* tree2);
void consolidate(Fheap *f);
void cuscading_cut();
void insert(Fheap *, int key);
void delete(Fheap *f, int key);
void decrease(Fheap *f, int key, int val);
int extract_min(Fheap *f);



void free_node(Node *n) {if (n) free(n);}


void free_fheap() {

}

Node *create_node(int key) {
    Node *n = (Node*) calloc(1, sizeof(Node));
    if (!n) perror("create_node");
    n->key = key;
    return n;
}

Fheap *init_fheap() {
    Fheap *f = (Fheap *) calloc(1, sizeof(Fheap));
    return f;
}

Node *unite(Node *tree1, Node* tree2) {
    printf("unite DEBUG\n");
    if (tree1 == NULL) return tree2;
    if (tree2 == NULL) return tree1;

    if (tree1->key > tree2->key) {
        Node *tmp = tree1;
        tree1 = tree2;
        tree2 = tmp;
    }

    if (tree2->prev) tree2->prev->next = tree2->next;
    if (tree2->next) tree2->next->prev = tree2->prev;
    tree2->prev = tree2->next = NULL;

    Node *head = tree1->child_head;
    if (head == NULL) 
        tree1->child_head = tree2;
    else {
        tree2->next = head->next;
        if (head->next) head->next->prev = tree2;
        head->next = tree2;
        tree2->prev = head;
    }
    
    return tree1;
}

void consolidate(Fheap *f) {
    Node *curr = f->root->next;
    
    while (curr != NULL) {
        Node *next = curr->next;

        Node *united_node = curr;
        int d = united_node->degree;

        while (d < MAX_DEGREE) {
            if (degrees[d] == NULL) {
                degrees[d] = united_node;
                break;
            }
            else {
                united_node = unite(degrees[d], united_node);
                united_node->degree++;
                degrees[d] = NULL;
                d = united_node->degree;
            }
            printf("inner while DEBUG\n");
        }

        curr = next;
        printf("outer while DEBUG\n");
    }
}

void cuscading_cut() {

}

void insert(Fheap *f, int key) {
    // O(1) doubly linked lazy 
    Node *new_node = create_node(key);
    handler[new_node->key] = new_node;
    
    Node *curr = f->root;
    if (curr == NULL) f->root = new_node;
    else {
        new_node->next = curr->next;
        if (curr->next) curr->next->prev = new_node;

        new_node->prev = curr;
        curr->next = new_node;
    }
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
        printf("key: %d, mark: %d, degree: %d, this: %d, prev: %d, next: %d, parent: %d, child_head %d\n",
                curr->key, curr->mark, curr->degree, curr, curr->prev, curr->next, curr->parent, curr->child_head);
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
            consolidate(fheap);
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