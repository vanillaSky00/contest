#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Node {
    int score;
    int temp;
    struct Node *next;
} Node;

void deleteAfter(Node* n) {
    // since we have dummy head and dummy tail so it all the same
    Node *deleted = n->next;
    n->next = deleted->next;
    deleted->next = NULL;
    free(deleted);
}

Node *combineSame(Node *n) {
    if (n == NULL || n->score == INT32_MIN) return NULL;

    Node *tmp = n;
    while (tmp && 
           tmp->next && 
           tmp->temp == tmp->next->temp) {

            tmp->score += tmp->next->score;
            deleteAfter(tmp); 
    }
    return n;
}

Node *mergeReport(Node *reportA, Node *reportB) {
    // get the actual head;
    reportA = combineSame(reportA);
    reportB = combineSame(reportB);
    if (reportA == NULL) return reportB;
    if (reportB == NULL) return reportA;
    
    // A always the max
    if (reportA->temp < reportB->temp) {
        Node *tmp = reportA;
        reportA = reportB;
        reportB = tmp;
    }

    Node *tail_A = reportA;
    Node *tail_B = reportB;
    while (tail_A && tail_A->next && tail_B && tail_B->next &&
          (tail_A->next->score != INT32_MIN || tail_B->next->score != INT32_MIN)) {
        
        Node *prev = NULL;
        while (tail_A->next->score != INT32_MIN && 
               tail_B->next->score != INT32_MIN &&
               tail_A->temp > tail_B->temp) {
            prev = tail_A;
            tail_A = tail_A->next;
        }

        if (tail_A->next->score == INT32_MIN || 
            tail_B->next->score == INT32_MIN) break;

        // if not go to dummy node in list then prev must not NULL, so insert to after prev
        Node *node = tail_B;
        tail_B = tail_B->next;
        
        tail_B->next = tail_A->next;
        tail_A->next = tail_B;
    }

    if (tail_A->score == INT32_MIN) {
        Node *dummy_tA = tail_A;
        // append rest B to A and remain dummy tail property
        tail_A->next = tail_B;
        while (tail_A->next != NULL) tail_A = tail_A->next;
        tail_A->next = dummy_tA;
    }
    // other case: B done, then all done

    reportA = combineSame(reportA);
    return reportA;
}

Node *insertAfter(Node *tail, Node *new) {
    new->next = tail->next;
    tail->next = new;
    return new;
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
        tail_A = insertAfter(dummy_hA, createNode(s, t));
    }
    insertAfter(tail_A, dummy_tA);

    while (n-- > 0) {
        if (scanf("%d%d", &s, &t) != 2) return -1;
        tail_B = insertAfter(dummy_hB, createNode(s, t));
    }
    insertAfter(tail_B, dummy_tB);

    Node *ans = mergeReport(dummy_hA->next, dummy_hB->next); // get the actual head

    bool isEmpty = true;
    Node *tmp = (ans == NULL) ? NULL : ans->next;
    while (tmp != NULL && tmp->score != INT32_MIN) {
        if (tmp->score == 0) continue;
        printf("%d %d\n", tmp->score, tmp->temp);
        tmp = tmp->next;
        isEmpty = false;
    }
    
    if (isEmpty) printf("0\n");

    return 0;
}