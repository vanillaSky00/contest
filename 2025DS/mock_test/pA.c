#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Node {
    int score;
    int temp;
    struct Node *next;
} Node;

void deleteNode(Node* n) {

}

Node *combineSame(Node *n) {

}

Node *mergeReport(Node *reportA, Node *reportB) {
    if (reportA == NULL) {
        combineSame(reportB);
        return reportB;
    }
    if (reportB == NULL) {
        combineSame(reportA);
        return reportA;
    }
    // A always the max
    if (reportA->temp < reportB->temp) {
        Node *tmp = reportA;
        reportA = reportB;
        reportB = tmp;
    }

    Node *tail_A = reportA;
    Node *tail_B = reportB;
    while (tail_A != NULL || tail_B != NULL) {

    }

    if (tail_A == NULL) {
        // put B to A and then
        tail_A->next = tail_B;
        combineSame(tail_A);
        return reportB;
    }
    // other case: B done, then all done

    return reportA;
}

Node *insert(Node *tail, Node *new) {
    new->next = tail->next;
    tail->next = new;
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

    Node *dummy_hA = (Node*) malloc(sizeof(Node));
    Node *dummy_hB = (Node*) malloc(sizeof(Node));
    Node *dummy_tA = (Node*) malloc(sizeof(Node));
    Node *dummy_tB = (Node*) malloc(sizeof(Node));
    dummy_hA->score = dummy_hA->temp = dummy_hB->score = dummy_hB->temp = INT32_MIN;
    dummy_tA->score = dummy_tA->temp = dummy_tB->score = dummy_tB->temp = INT32_MIN;
    
    Node *tail_A, *tail_B;
    int s, t;
    while (m-- > 0) {
        if (scanf("%d%d", &s, &t) != 2) return -1;
        tail_A = insert(dummy_hA, createNode(s, t));
    }
    insert(tail_A, dummy_tA);

    while (n-- > 0) {
        if (scanf("%d%d", &s, &t) != 2) return -1;
        tail_B = insert(dummy_hB, createNode(s, t));
    }
    insert(tail_B, dummy_tB);

    Node *ans = mergeReport(dummy_hA->next, dummy_hB->next);

    bool isEmpty = true;
    Node *tmp = (ans->next == NULL) ? NULL : ans->next;
    while (tmp != NULL && tmp->score != INT32_MIN) {
        if (tmp->score == 0) continue;
        printf("%d %d\n", tmp->score, tmp->temp);
        tmp = tmp->next;
        isEmpty = false;
    }
    
    if (isEmpty) printf("0\n");

    return 0;
}