#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#define DEBUG(msg,...) printf("DEBUG: " msg "\n" , ##__VA_ARGS__)
#define DEBUG(msg,...)
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
void insert_node(Fheap *f, Node *node);
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
    DEBUG("unite");
    if (tree1 == NULL) return tree2;
    if (tree2 == NULL) return tree1;

    if (tree1->key > tree2->key) {
        Node *tmp = tree1;
        tree1 = tree2;
        tree2 = tmp;
    }

    // this cause loop
    if (tree2->prev) tree2->prev->next = tree2->next;
    if (tree2->next) tree2->next->prev = tree2->prev;
    tree2->prev = tree2->next = NULL;

    Node *head = tree1->child_head;
    if (head == NULL) 
        tree1->child_head = tree2;
    else {
        tree2->next = head;
        head->prev = tree2;
        tree1->child_head = tree2; // always insert front of child head
    }
    
    tree2->parent = tree1;
    return tree1;
}

void consolidate(Fheap *f) {
    Node *degrees[MAX_DEGREE] = {NULL};

    Node *curr = f->root;
    
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
            DEBUG("consolidate: inner while");
        }

        curr = next;
        DEBUG("consolidate: outter while");
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

void insert_node(Fheap *f, Node *node) {
    // O(1) doubly linked lazy 
    
    Node *curr = f->root;
    if (curr == NULL) f->root = node;
    else {
        node->next = curr->next;
        if (curr->next) curr->next->prev = node;

        node->prev = curr;
        curr->next = node;
    }
}

void delete(Fheap *f, int key) {
    Node *t = handler[key];
    handler[key] = NULL;

    // 4 cases with or without child/ parent
    if (t->child_head != NULL) {
        Node *child = t->child_head;

        while (child != NULL) {
            Node *next = child->next;

            child->next = NULL;
            child->prev = NULL;
            child->parent = NULL;
            insert_node(f, child);

            child = next;
        }
    }

    if (t->parent != NULL) {
        Node *p = t->parent;
        p->mark++;
        p->degree--;

        if (p->child_head == t) {
            p->child_head = t->next; 
            if (t->next) t->next->prev = NULL;
            // need change parent here? or is done?
        }
        else {
            if (t->prev) t->prev->next = t->next;
            if (t->next) t->next->prev = t->prev;
        }

        if (p->mark == 2) {
            p->mark = 0;
            delete(f, p->key);
        }
    }
    else { // handling root
        if (t->prev) t->prev->next = t->next;
        if (t->next) t->next->prev = t->prev;
        if (f->root == t) f->root = t->next;
    }

    free_node(t);
}

void decrease(Fheap *f, int key, int val) {
    Node *target = handler[key];
    
}

int extract_min(Fheap *f) {
    int min = f->min;
    delete(f, min);
    DEBUG("extract-min\n");
    return min;
}


int cmp_tree(const void *a, const void *b){
    // compare degree first and then key
    const Node *x = *(const Node **)a;
    const Node *y = *(const Node **)b;

    if (x->degree < y->degree) return -1;
    if (x->degree > y->degree) return 1;

    if (x->key < y->key) return -1;
    if (x->key > y->key) return 1;

    return 0;
}

// Node **setup_print(Node *curr, int *size) {
//     int s = 0;
//     while (curr != NULL) {
//         s++;
//         curr = curr->next;
//     }

//     Node **trees = (Node **) malloc(s * sizeof(Node*));
//     int idx = 0;
//     while (curr != NULL) {
//         trees[idx++] = curr;
//         curr = curr->next;
//     }

//     qsort(trees, s, sizeof(Node*), cmp_tree);
//     *size = s;
//     return trees;
// }

// void print_forest(Fheap *f) {
//     // print each tree by degree then by key
//     if (f->root == NULL) return;

//     int tree_size = 0;
//     Node **trees = setup_print(f->root, &tree_size);
//     int top = 0;

//     while (top < tree_size) {
//         Node *root = trees[top++];
//         print_node(root);
        
//         int layer_size = 0;

//     }

    
//     free(trees);
// }

void test_print(Fheap *f) {
    Node *curr = f->root;


    while (curr != NULL) {
        DEBUG("key: %d, mark: %d, degree: %d, this: %d, prev: %d, next: %d, parent: %d, child_head %d\n",
              curr->key, curr->mark, curr->degree, curr, curr->prev, curr->next, curr->parent, curr->child_head);
        
        if (curr->child_head != NULL) {
            DEBUG("\n\nfound child: \n\n");
            Node *child = curr->child_head;
            while (child != NULL) {
                DEBUG("key: %d, mark: %d, degree: %d, this: %d, prev: %d, next: %d, parent: %d, child_head %d\n",
                      child->key, child->mark, child->degree, child, child->prev, child->next, child->parent, child->child_head);
                child = child->next;
            }
            DEBUG("\n\ndone: \n\n");
        }

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