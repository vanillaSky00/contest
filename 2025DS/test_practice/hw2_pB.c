#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int key;
} Node;

Node *create_node(int key) {
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->key = key;
    return node;
}

Node *insert(Node *root, int key) {
    if (!root) return create_node(key);
    if (key > root->key) root->right = insert(root->right, key); 
    else root->left = insert(root->left, key);
    return root; 
}

Node *find_rsuccessor(Node *root) {
    root = root->right;

    while (root->left) {
        root = root->left;
    }
    return root;
}

Node *delete(Node *root, int key) {
    if (root == NULL) return root;

    if (key < root->key) root->left = delete(root->left, key);
    else if (key > root->key) root->right = delete(root->right, key);
    else {
        //find the node with the key

        // 0 kids or only right
        if (!root->left) {
            Node *tmp = root->right;
            free(root);
            return tmp;
        }

        // 0 kid or only left
        if (!root->right) {
            Node *tmp = root->left;
            free(root);
            return tmp;
        }

        // 2 kids
        if (root->left && root->right) {
            Node *succ = find_rsuccessor(root);
            root->key = succ->key;
            root->right = delete(root->right, succ->key);
        }
    }
    return root;
}

void print_tree(Node *root) {
    if (!root) return;

    Node *q[3001];
    int front = 0, rear = 0;

    q[rear++] = root;
    while (rear > front) {
        Node *curr = q[front++];
        printf("%d ", curr->key);
        
        if (curr->left != NULL) q[rear++] = curr->left;
        if (curr->right != NULL) q[rear++] = curr->right;
    }
}

int main() {
    char cmd[12];
    int x;
    Node *root = NULL;

    while (true) {
        scanf("%s", cmd);
        if (strcmp(cmd, "insert") == 0) {
            scanf("%d", &x);
            root = insert(root, x);
        }
        else if (strcmp(cmd, "delete") == 0) {
            scanf("%d", &x);
            root = delete(root, x);
        }
        else if (strcmp(cmd, "exit") == 0) {
            print_tree(root);
            return 0;
        }
        else {
            printf("Invalid arguemnts\n");
        }
    }
}

// This insert cause wrong if delete the last node and root becomes null 
// and we get error from the following insert
// void insert(Node *root, int key) {
//     if (root->key == INT32_MAX) {
//         root->key = key;
//         return;
//     }

//     Node *n = create_node(key);
    
//     while (root != NULL) {
//         if (key < root->key) {
//             if (root->left != NULL) root = root->left;
//             else {
//                 root->left = n;
//                 break;
//             }
//         }
//         else {
//             if (root->right != NULL) root = root->right;
//             else {
//                 root->right = n;
//                 break;
//             } 
//         }
//     }
// }