#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Node {
    long long score;
    int temp;
    struct Node *next;
} Node;

void freeNode(Node* n) {
    if (n) free(n);
}

Node *compressAndClean(Node *head) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *curr = head;

    while (curr != NULL) {
        while (curr->next != NULL && curr->temp == curr->next->temp) {
            Node *duplicated = curr->next;
            curr->score += duplicated->score;
            curr->next = duplicated->next;
            duplicated->next = NULL;
            freeNode(duplicated);
        }

        if (curr->score == 0) {
            prev->next = curr->next;
            freeNode(curr);
            curr = prev->next;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}

Node *mergeSortedLists(Node *listA, Node *listB) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (listA && listB) {
        if (listA->temp > listB->temp) {
            tail->next = listA;
            listA = listA->next;
        }
        else if (listA->temp < listB->temp) {
            tail->next = listB;
            listB = listB->next;
        }
        else {
            // append both
            tail->next = listA;
            listA = listA->next;
            tail = tail->next;

            tail->next = listB;
            listB = listB->next;
        }
        tail = tail->next;
    }

    if (listA) tail->next = listA;
    if (listB) tail->next = listB;
    return dummy.next;
}

Node *mergeReport(Node *reportA, Node *reportB) {
    Node *mergerHead = mergeSortedLists(reportA, reportB);
    return compressAndClean(mergerHead);
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

    long long s;
    int t;

    Node dummyA;
    Node *tailA = &dummyA;
    dummyA.next = NULL;
    while (m-- > 0) {
        if (scanf("%lld%d", &s, &t) != 2) return -1;
        tailA->next = createNode(s, t);
        tailA = tailA->next;
    }

    Node dummyB;
    Node *tailB = &dummyB;
    dummyB.next = NULL;
    while (n-- > 0) {
        if (scanf("%lld%d", &s, &t) != 2) return -1;
        tailB->next = createNode(s, t);
        tailB = tailB->next;
    }

    Node *res = mergeReport(dummyA.next, dummyB.next); // get the actual head

    if (res == NULL) {
        printf("0\n");
    }
    else {
        while (res != NULL) {
            printf("%lld %d\n", res->score, res->temp);
            res = res->next;
        }
    }

    return 0;
}