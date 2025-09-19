#include <stdio.h>
#include <stdlib.h>

int main() {
    int t = 0;
    scanf("%d", &t);
    int* arr = (int*) malloc(sizeof(*arr) * t);

    for (int i = 0; i < t; i++) {
        scanf("%d", &arr[i]);
    }

    int* ans = nearestSmallerElement(t, arr);
    for (int i = 0; i < t; i++) {
        printf("%d,", ans[i]);
    }

    return 0;
}