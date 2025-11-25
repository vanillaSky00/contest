#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Fheap {
    /* data */
} Fheap;

void insert(Fheap *f, int key) {
    printf("insert %d\n", key);
}

void delete(Fheap *f, int key) {
    printf("delete %d\n", key);
}

void decrease(Fheap *f, int key, int val) {
    printf("decrease %d %d\n", key, val);
}

int extract_min(Fheap *f) {
    printf("extract-min\n");
    return 0;
}

#define MAX_BUFF 12
int main(void) {

    char *cmd = malloc(MAX_BUFF);
    int key;
    int val;
    Fheap* fheap = (Fheap*) malloc(sizeof(Fheap));

    while (true) {
        if (scanf("%11s", cmd) != 1)   // safe input
            break;

        if (strcmp(cmd, "insert") == 0) {
            scanf("%d", &key);
            insert(fheap, key);
        } 
        else if (strcmp(cmd, "delete") == 0) {
            scanf("%d", &key);
            delete(fheap, key);
        }
        else if (strcmp(cmd, "decrease") == 0) {
            scanf("%d", &key);
            scanf("%d", &val);
            decrease(fheap, key, val);
        }
        else if (strcmp(cmd, "extract-min") == 0) {
            extract_min(fheap);
        }
        else if (strcmp(cmd, "exit") == 0) {
            return 0;
        }
        else {
            fprintf(stderr, "Invalid arguments\n");
            return -1;
        }
    }

    free(cmd);
    return 0;
}