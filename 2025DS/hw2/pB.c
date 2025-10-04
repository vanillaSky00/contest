#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int SIZE = 0;

typedef struct TreeNode {
    struct TreeNode* left;
    struct TreeNode* right;
    int val;
} TreeNode; 

TreeNode* createNode(int val) {
    TreeNode* n = (TreeNode*) malloc(sizeof(*n));
    if (n == NULL) exit(EXIT_FAILURE);
    n->left = NULL;
    n->right = NULL;
    n->val = val;
    return n;
}

TreeNode* insertNode(TreeNode* root, int val) {
    TreeNode* n = createNode(val);
    if (root == NULL) {
        SIZE++;
        return n;
    }
    TreeNode* curr = root;
    TreeNode* prev = NULL;
    while (curr != NULL) {
        prev = curr;
        curr = (val < curr->val) ? curr->left : curr->right;
    }

    if (val < prev->val) prev->left = n;
    else prev->right = n;

    SIZE++;
    return root;
}

TreeNode* rightSuccessor(TreeNode* node) {// right smallest
    if (node == NULL) return NULL;
    node = node->right;
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}

TreeNode* deleteNode(TreeNode* root, int val) {
    if (root == NULL) return root;
    if (val < root->val) root->left = deleteNode(root->left, val);
    else if (val > root->val) root->right = deleteNode(root->right, val);
    else {
        // 0 child or only has right child
        if (root->left == NULL) {
            TreeNode* tmp = root->right;
            free(root);
            SIZE--;
            return tmp;
        } 
        // 0 child or only has left child
        else if (root->right == NULL) {
            TreeNode* tmp = root->left;
            free(root);
            SIZE--;
            return tmp;
        }
        // has 2 child
        else {
            TreeNode* succ = rightSuccessor(root);
            root->val = succ->val;
            root->right = deleteNode(root->right, succ->val);
        }
    }
    return root;
}

void levelOrder(TreeNode* node) {
    if (node == NULL || SIZE <= 0) puts("");

    TreeNode** q = (TreeNode**) malloc(sizeof(*q) * SIZE);
    if (q == NULL) exit(EXIT_FAILURE);
    int front = 0;
    int rear = 0;
    q[rear++] = node;
    
    while (rear > front) {
        TreeNode* curr = q[front++];
        printf("%d ", curr->val);
        if (curr->left != NULL) q[rear++] = curr->left;
        if (curr->right != NULL) q[rear++] = curr->right;
    }
    free(q);
}

int main(void) {
    char cmd[7];
    int val;
    TreeNode* root = NULL;

    while (true) {
        scanf("%s", cmd);

        if (strncmp(cmd, "insert", 6) == 0) {
            if (scanf("%d", &val) != 1) exit(EXIT_FAILURE);
            root = insertNode(root, val);
        }
        else if (strncmp(cmd, "delete", 6) == 0) {
            if (scanf("%d", &val) != 1) exit(EXIT_FAILURE);
            root = deleteNode(root, val);
        } 
        else if (strncmp(cmd, "exit", 4) == 0) {
            levelOrder(root);
            exit(EXIT_SUCCESS);
        }
        else {
            printf("Invalid commands\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}