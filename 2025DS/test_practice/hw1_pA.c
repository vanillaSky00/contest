#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *solver(int n, int *nums) {
    int *ans = (int*) malloc(sizeof(int) * n);
    int stack[n];
    int top = -1;

    for (int i = 0; i < n; i++) {
        while (top > -1 && nums[stack[top]] >= nums[i]) top--;
        ans[i] = (top == -1) ? -1 : i - stack[top];
        stack[++top] = i;  
    }

    return ans;
}

int main(void) {
    int n;
    scanf("%d", &n);

    int nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int *ans = solver(n, nums);

    bool isEmpty = true;
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) isEmpty = false;
        printf("%d ", ans[i]);
    }
    printf("\n");

    if (isEmpty) {
        printf("EMPTY\n");
    }
    else {
        for (int i = 0; i < n; i++) {
            if (ans[i] != -1) {
                printf("%d ", ans[i]);
            }
        }
    }

    free(ans);
    return 0;
}