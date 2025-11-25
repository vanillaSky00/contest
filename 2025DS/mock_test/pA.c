#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int score;
    int temp;
    struct Node *next;
} Node;

Node *mergeReport(Node *reportA, Node *reportB) {
    return NULL;
}

void insert(Node *head, Node *new) {

}

Node *createNode(int s, int t) {
    Node *new = (Node*) malloc(sizeof(Node));
    new->score = s;
    new->temp = t;
    new->next = NULL;
    return new;
}

int main(void) {
    int m, n;
    if (scanf("%d%d", &m, &n) != 2) return -1;

    Node *dummy_A = (Node*) malloc(sizeof(Node));
    Node *dummy_B = (Node*) malloc(sizeof(Node));

    int s, t;
    while (m-- > 0) {
        if (scanf("%d%d", &s, &t) != 2) return -1;
        insert(dummy_A, createNode(s, t));
    }

    while (n-- > 0) {
        if (scanf("%d%d", &s, &t) != 2) return -1;
        insert(dummy_B, createNode(s, t));
    }

    Node *ans = mergeReport(dummy_A, dummy_B);

    Node *tmp = (ans->next == NULL) ? NULL : ans->next;
    while (tmp != NULL) {
        printf("%d %d\n", tmp->score, tmp->temp);
        tmp = tmp->next;
    }

    return 0;
}