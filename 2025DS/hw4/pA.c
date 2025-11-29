#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
//#define DEBUG(msg,...) printf("DEBUG: " msg "\n" , ##__VA_ARGS__)
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

void free_node(Node *n) {if (n) free(n);}

int find_min(Fheap *f) {
    Node *curr = f->root;
    int min = INT32_MAX;
    while (curr != NULL) {
        if (curr->key < min) min = curr->key;
        curr = curr->next;
    }
    return min;
}

Node *create_node(int key) {
    Node *n = (Node*) calloc(1, sizeof(Node));
    if (!n) perror("create_node");
    n->key = key;
    return n;
}

Fheap *init_fheap() {
    Fheap *f = (Fheap *) calloc(1, sizeof(Fheap));
    f->min = INT32_MAX;
    return f;
}

void add_root(Fheap *f, Node *x) {
    // add back to root list, and prepare for it
    x->prev = NULL;
    x->next = NULL;
    x->parent = NULL;
    x->mark = 0;

    if (f->root == NULL) f->root = x;
    else {
        // //insert at the HEAD (O(1))
        // x->next = f->root;
        // f->root->prev = x;
        // f->root = x;
        // Find the TAIL and append
        Node *curr = f->root;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = x;
        x->prev = curr;
    }
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
        // tree2->next = head;
        // head->prev = tree2;
        // tree1->child_head = tree2; // always insert front of child head
        Node *curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = tree2;
        tree2->prev = curr;
    }
    
    tree2->parent = tree1;
    return tree1;
}

void consolidate(Fheap *f) {
    Node *degrees[MAX_DEGREE] = {NULL};
    Node *curr = f->root;
    int max_d = 0;

    while (curr != NULL) {
        Node *next = curr->next;

        Node *united_node = curr;
        int d = united_node->degree;

        while (d < MAX_DEGREE) {
            if (degrees[d] == NULL) {
                degrees[d] = united_node;
                if (max_d < d) max_d = d;
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

    // rebuild f heap from the degrees
    f->min = INT32_MAX;
    f->root = NULL;

    for (int i = 0; i <= max_d; i++) {
        if (degrees[i] != NULL) {
            add_root(f, degrees[i]);

            if (degrees[i]->key < f->min) f->min = degrees[i]->key;
        }
    }
}

void cascading_cut(Fheap *f, Node *x) {
    if (f == NULL || x == NULL) return;
    // Stop if x is a root, and root does not mark
    if (x->parent == NULL) return;

    if (x->mark == 0) {
        x->mark = 1;
    }
    else { 

        if (x->prev) x->prev->next = x->next;
        if (x->next) x->next->prev = x->prev;

        Node *p = x->parent;
        p->degree--;

        if (p->child_head == x) {
            p->child_head = x->next; 
            if (x->next) x->next->prev = NULL;
            // need change parent here? or is done?
        }

        add_root(f, x);

        cascading_cut(f, p);
    }
}

void insert(Fheap *f, int key) {
    // O(1) doubly linked lazy 
    Node *new_node = create_node(key);
    handler[new_node->key] = new_node;
    
    if (f->root == NULL || key < f->min) 
        f->min = new_node->key;
    
    add_root(f, new_node);
}

Node *delete(Fheap *f, int key) {
    Node *t = handler[key];
    if (!t) return NULL;
    handler[key] = NULL;

    // 4 cases with or without child/ parent
    if (t->child_head != NULL) {
        Node *child = t->child_head;

        while (child != NULL) {
            Node *next = child->next;

            add_root(f, child);

            child = next;
        }
    }

    // handling parent, itself, neighbor
    if (t->prev) t->prev->next = t->next;
    if (t->next) t->next->prev = t->prev;
    if (f->root == t) f->root = t->next; // handling root

    Node *p = t->parent;
    if (p != NULL) {
        p->degree--;

        if (p->child_head == t) {
            p->child_head = t->next; 
            if (t->next) t->next->prev = NULL;
            // need change parent here? or is done?
        }
    }

    if (t->key == f->min) f->min = find_min(f);
    free_node(t);
    return p;
}

Node *decrease(Fheap *f, int key, int val) {
    Node *x = handler[key];
    if (!x) return NULL; 

    x->key -= val;
    handler[key] = NULL;
    handler[x->key] = x;
    if (x->key < f->min) f->min = x->key;
    
    Node *p = x->parent;
    if (p != NULL && x->key < p->key) {
        if (x->prev) x->prev->next = x->next;
        if (x->next) x->next->prev = x->prev;

        p->degree--;

        if (p->child_head == x) {
            p->child_head = x->next; 
            if (x->next) x->next->prev = NULL;
        }
        
        add_root(f, x);
        return p;
    }

    return NULL;
}

int extract_min(Fheap *f) {
    int min = f->min;
    delete(f, min); // already update min
    DEBUG("extract-min\n");
    return min;
}

int cmp_roots(const void *a, const void *b){
    // compare degree first and then key
    const Node *x = *(const Node **)a;
    const Node *y = *(const Node **)b;

    if (x->degree < y->degree) return -1;
    if (x->degree > y->degree) return 1;

    if (x->key < y->key) return -1;
    if (x->key > y->key) return 1;

    return 0;
}

int cmp_keys(const void *a, const void *b) {
    const Node *x = *(const Node **)a;
    const Node *y = *(const Node **)b;
    if (x->key < y->key) return -1;
    if (x->key > y->key) return 1;
    return 0;
}

Node **collect_subtrees(Node *head, int *count) {
    int s = 0;
    Node *curr = head;

    while (curr != NULL) {
        s++;
        curr = curr->next;
    }
    *count = s;
    if (s == 0) return NULL;

    Node **trees = (Node **) malloc(s * sizeof(Node*));
    curr = head;
    int idx = 0;
    while (curr != NULL) {
        trees[idx++] = curr;
        curr = curr->next;
    }
    
    return trees;
}

void print_tree_bfs(Node *root) {
    if (root == NULL) return;

    Node **curr_level = (Node**)malloc(NODE_CAP * sizeof(Node*));
    Node **next_level = (Node**)malloc(NODE_CAP * sizeof(Node*));
    int curr_count = 0;

    curr_level[0] = root;
    curr_count = 1;
    printf("%d", root->key);

    while (curr_count > 0) {
        int next_count = 0;

        for (int i = 0; i < curr_count; i++) {
            Node *parent = curr_level[i];
            Node *child = parent->child_head;
            while (child != NULL) {
                next_level[next_count++] = child;
                child = child->next;
            }
        }

        if (next_count > 0) {
            qsort(next_level, next_count, sizeof(Node*), cmp_keys);
            for (int i = 0; i < next_count; i++) printf(" %d", next_level[i]->key);
        }

        Node **temp = curr_level;
        curr_level = next_level; 
        next_level = temp;
        curr_count = next_count;
    }
    printf("\n");
    free(curr_level);
    free(next_level);
}

void print_forest(Fheap *f) {
    // print each tree by degree then by key
    if (f->root == NULL) return;

    int root_count = 0;
    Node **roots = collect_subtrees(f->root, &root_count);
    qsort(roots, root_count, sizeof(Node*), cmp_roots);

    for (int i = 0; i < root_count; i++) print_tree_bfs(roots[i]);

    free(roots);
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
            Node *p = delete(fheap, key);
            cascading_cut(fheap, p);
            consolidate(fheap);
        }
        else if (strcmp(cmd, "decrease") == 0) {
            scanf("%d", &key);
            scanf("%d", &val);
            Node *p = decrease(fheap, key, val);
            cascading_cut(fheap, p);
        }
        else if (strcmp(cmd, "extract-min") == 0) {
            extract_min(fheap);
            //cascading_cut(fheap, p); // must root no parent
            consolidate(fheap);
        }
        else if (strcmp(cmd, "exit") == 0) {
            print_forest(fheap);
            free(cmd);
            return 0;
        }
        else {
            fprintf(stderr, "Invalid arguments\n");
            return -1;
        }
    }
}