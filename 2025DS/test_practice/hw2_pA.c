#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *arr;
    int size;
} Heap;

static inline int comp(int x, int y) {return x > y;}

static inline void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// careful (-1+0) / 2 =0 and 1 or 2 parent is 0
void heapifyUp(Heap *h, int idx) {
    while (idx > 0) { 
        int parent = (idx - 1) / 2;
        if(!comp(h->arr[idx], h->arr[parent])) break;
        swap(&h->arr[idx], &h->arr[parent]);
        idx = parent;
    }
}

void heapifyDown(Heap *h, int idx) {
    int largest = idx;
    int left = idx * 2 + 1;
    int right = left + 1;

    if (left < h->size && comp(h->arr[left], h->arr[largest])) largest = left; 
    if (right < h->size && comp(h->arr[right], h->arr[largest])) largest = right;
    if (largest != idx) {
        swap(&h->arr[idx], &h->arr[largest]);
        heapifyDown(h, largest);
    }
}

void insert(Heap *h, int key) {
    h->arr[h->size] = key;
    heapifyUp(h, h->size);
    h->size++;
}

int extractMax(Heap *h) {
    int max = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return max;
}

void battle(Heap *h) {
    int merged_key = extractMax(h) - extractMax(h);
    insert(h, merged_key);
}

void update(Heap *h, int idx, int new_key) {
    int old_key = h->arr[idx];
    h->arr[idx] = new_key;
    if (old_key < new_key) heapifyUp(h, idx);
    else heapifyDown(h, idx);
}


#define INIT_SIZE 250001
int main(void) {
    Heap* hp = (Heap*) malloc(sizeof(Heap));
    hp->size = 0;
    hp->arr = (int*) malloc(sizeof(int) * INIT_SIZE);

    int n;
    scanf("%d", &n);
    while (n-- > 0) {
        int command;
        scanf("%d", &command);

        if (command == 0) {
            int val;
            scanf("%d", &val);
            insert(hp, val);
        }
        else if (command == 1) {
            battle(hp);
        }
        else if (command == 2) {
            int idx, delta;
            scanf("%d%d", &idx, &delta);
            update(hp, idx, hp->arr[idx] + delta);
        }
        else {
            printf("Invalid commands");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < hp->size; i++) {
        printf("%d ", hp->arr[i]);
    }

    free(hp->arr);
    free(hp);
    return 0;
}