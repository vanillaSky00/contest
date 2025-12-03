#include <stdio.h>
#include <stdlib.h>

int* nearestSmallerElement(int n, int* arr);

int main() {
    int t = 0;
    scanf("%d", &t);
    int* arr = (int*) malloc(sizeof(*arr) * t);

    for (int i = 0; i < t; i++) {
        scanf("%d", &arr[i]);
    }

    int* ans = nearestSmallerElement(t, arr);

    int isEmpty = 1;
    for (int i = 0; i < t; i++) {
        if (ans[i] != -1) isEmpty = 0;
        printf("%d ", ans[i]);
    }

    printf("\n");

    if (isEmpty) printf("EMPTY");
    else {
        for (int i = 0; i < t; i++) {
            if (ans[i] != -1) printf("%d ", ans[i]);
        }
    }

    free(ans);
    return 0;
}

int* nearestSmallerElement(int n, int* arr) {
    int* res = (int*) malloc(sizeof(*res) * n);
    int* stack = (int*) malloc(sizeof(*stack) * n);
    // idx stored in stack
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top != -1 && top < n && arr[stack[top]] >= arr[i]) {
            top--;
        }
        res[i] = (top == -1) ? -1 : i - stack[top];
        stack[++top] = i;
    }
    free(stack);
    return res;
}