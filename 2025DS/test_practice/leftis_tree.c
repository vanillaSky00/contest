#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int key;
    int s;
} Node;

void swap(Node **x, Node **y) {
    Node *tmp = *x;
    *x = *y;
    *y = tmp;
}

Node *meld(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;

    if (x->key > y->key) swap(&x, &y);

    x->right = meld(x->right, y); // so right will never null 

    if (!x->left) {
        x->left = x->right;
        x->right = NULL;
    }
    else {
        if (x->left->s < x->right->s) swap(&x->left, &x->right);
        x->s = x->right->s + 1;
    }

    return x;
}

Node *meld_v2(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;

    if (x->key > y->key) swap(&x, &y);

    x->right = meld_v2(x->right, y);

    int ls = x->left ? x->left->s : -1;
    int rs = x->right ? x->right->s : -1;

    if (ls < rs) swap(&x->left, &x->right);

    x->s = (x->right ? x->right->s : -1) + 1;
    return x;
}

void insert(Node **root, int key) {
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->key = key;
    *root = meld(*root, node);
}

int extractMin(Node **root) {
    Node *r = *root;
    int min = r->key;
    *root = meld(r->left, r->right);
    free(r);
    return min;
}

void print_leftis_tree(Node *root) {

}

int main(void) {

    return 0;
}