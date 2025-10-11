#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct maxHeap {
    int* data;
    int size;
    int capacity;
} maxHeap;

maxHeap* create_maxHeap(int size) {
    maxHeap* hp = (maxHeap*) malloc(sizeof(maxHeap));
    hp->data = (int*) malloc(sizeof(int) * size);
    hp->capacity = size;
    hp->size = 0;
    return hp;
}

static void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// be careful of input is hp->data[idx] not idx
static inline int compInt(int x, int y) {
    return x - y;
}

static void heapifyUp(maxHeap* hp, int i) { // becareful parent not update
    if (hp == NULL) return;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compInt(hp->data[i], hp->data[parent]) > 0) {
            swap( &(hp->data[parent]), &(hp->data[i]) );
            i = (i - 1) / 2;
        }
        else break;
    }
}

static void heapifyDown(maxHeap* hp, int i) {
    if (hp == NULL) return;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int n = hp->size;

    if (left < n && compInt(hp->data[left], hp->data[largest]) > 0) largest = left;
    if (right < n && compInt(hp->data[right], hp->data[largest]) > 0) largest = right;

    if (largest != i) {
        swap( &(hp->data[i]) , &(hp->data[largest]) );
        heapifyDown(hp, largest);
    }
}

static void resize_heap(maxHeap* hp, int new_capacity) {
    if (hp == NULL) return;
    hp->data = (int*) realloc(hp->data, sizeof(int) * new_capacity);
    hp->capacity = new_capacity;
}

static void insert(maxHeap* hp, int val) {
    if (hp == NULL) return;
    if (hp->size == hp->capacity) resize_heap(hp, 2 * hp->capacity);

    hp->data[hp->size] = val; 
    hp->size++;
    heapifyUp(hp, hp->size - 1);// be careful of the hp size and the idx to heapify in insert and extract
}

static void update(maxHeap* hp, int idx, int val) {
    if (hp == NULL || idx < 0 || idx >= hp->size) return;
    
    int old_val = hp->data[idx];
    hp->data[idx] = val;
    if (val > old_val) heapifyUp(hp, idx);
    else if (val < old_val) heapifyDown(hp, idx);
}

static int extract(maxHeap* hp) {
    if (hp == NULL || hp->size == 0) return INT32_MIN;
    int ex = hp->data[0];

    if (hp->size == 1) { 
        hp->size--; 
        return ex;
    }
    swap( &(hp->data[0]), &(hp->data[hp->size - 1]) );
    hp->size--;
    heapifyDown(hp, 0);
    return ex;
}

static int findIdxByVal(maxHeap* hp, int val) {
    for (int i = 0; i < hp->size; i++) 
        if (hp->data[i] == val) return i;
    return -1;
}

static void delete(maxHeap* hp, int val) {
    if (hp == NULL || hp->size == 0) return;
    int idx = findIdxByVal(hp, val);
    if (idx == -1) return;

    update(hp, idx, INT32_MAX);
    extract(hp);
}

static void levelOrder(maxHeap* hp) {
    for (int i = 0; i < hp->size; i++) {
        printf("%d ", hp->data[i]);
    }
}

#define INIT_SIZE 250001
int main(void) {
    maxHeap* hp = create_maxHeap(INIT_SIZE);

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
            int m1, m2;
            m1 = extract(hp);
            m2 = extract(hp);
            m1 -= m2;
            insert(hp, m1);
        }
        else if (command == 2) {
            int idx, delta;
            scanf("%d%d", &idx, &delta);
            update(hp, idx, hp->data[idx] + delta);
        }
        else {
            printf("Invalid commands");
            exit(EXIT_FAILURE);
        }
    }

    levelOrder(hp);
    free(hp->data);
    free(hp);
    return 0;
}