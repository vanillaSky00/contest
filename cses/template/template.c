#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *a = (int*)malloc(sizeof(int) * n);
    int *b = (int*)malloc(sizeof(int) * n);
    if (!a || !b) return 0;

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a[i], &b[i]);
    }

    // ----- YOUR LOGIC HERE -----
    long long ans = 0;
    // ---------------------------

    printf("%lld\n", ans);

    free(a); free(b);
    return 0;
}
