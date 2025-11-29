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
void insert(Node *root, Node *new_node);
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
    Fheap *f = (Fheap *) malloc(sizeof(Fheap));
    
    Node *dummy_head = (Node *) create_node(INT32_MIN); 
    dummy_head->degree = -1;
    f->root = dummy_head;
    return f;
}

Node *unite(Node *tree1, Node* tree2) {
    if (tree1 == NULL) return tree2;
    if (tree2 == NULL) return tree1;

    if (tree1->key > tree2->key) {
        Node *tmp = tree1;
        tree1 = tree2;
        tree2 = tmp;
    }

    if (tree1->child_head == NULL) tree1->child_head = tree2;
    else insert(tree1->child_head, tree2);
    return tree1;
}

void consolidate(Fheap *f) {
    Node *curr = f->root->next;
    Node *org_next = curr->next;
    while (curr != NULL) {

        Node *united_node = curr;
        for (int d = curr->degree; d < MAX_DEGREE; d++) {
            if (degrees[d] == NULL) {
                degrees[d] = united_node;
                break;
            }
            else {
                united_node = unite(curr, degrees[d]);
                united_node->degree++;
                degrees[d] = NULL;
            }
        }

        curr = org_next;
    }
}

void cuscading_cut() {

}

void insert(Node *n1, Node *n2) {
    // O(1) doubly linked lazy 

    n2->next = n1->next;
    if (n1->next) n1->next->prev = n2;   
    n1->next = n2;
    n2->prev = n1;

    n2->parent = n1->parent;
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
            Node *new_node = create_node(key); // this would avoid duplicate code for insert by node or key
            handler[new_node->key] = new_node;
            insert(fheap->root, new_node);
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