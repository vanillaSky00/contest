#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// reverse the time line technique
typedef struct DSU {
    int* parent;
    int* rank;
} DSU;

int find(DSU* dsu, int x) {
    return (dsu->parent[x] == x) ? x : (dsu->parent[x] = find(dsu, dsu->parent[x]));
}

bool union_find(DSU* dsu, int x, int y) {
    x = find(dsu, x);
    y = find(dsu, y);
    if (x == y) return false; // if already in same group
    
    if (dsu->rank[x] > dsu->rank[y]) {
        dsu->parent[y] = x;
    } 
    else if (dsu->rank[x] < dsu->rank[y]) {
        dsu->parent[x] = y;
    }
    else {
        dsu->parent[x] = y;
        dsu->rank[y]++;
    }
    return true; 
}

int* solver(int** bridges, int* collapse, int n, int m, int q) {
    DSU* dsu    = (DSU*) malloc(sizeof(DSU));
    dsu->parent = (int*) malloc(sizeof(int) * n);
    dsu->rank   = (int*) calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) dsu->parent[i] = i;

    bool* is_collapsed = (bool*) calloc(m, sizeof(bool));
    for (int i = 0; i < q; i++) is_collapsed[collapse[i] - 1] = true;
    
    for (int i = 0; i < m; i++) {
        if (!is_collapsed[i]) {
            union_find(dsu, bridges[i][0], bridges[i][1]);
        }
    }

    // find compression all nodes
    for (int i = 0; i <= n; i++) {
        find(dsu, i);
    }

    bool* is_root = (bool*) calloc(n, sizeof(bool));
    int group_num = 0;
    for (int i = 0; i < n; i++) {
        int r = dsu->parent[i];
        if (is_root[r] == false) {
            group_num++;
            is_root[r] = true;
        }
    }

    int* res = (int*) malloc(sizeof(int) * (q + 1));
    res[q] = group_num;

    // reverse: add from last
    for (int i = q - 1; i >= 0; i--) {
        int c = collapse[i];
        if(union_find(dsu, bridges[c][0], bridges[c][1]) == false) group_num--;
        res[i] = group_num;
    }

    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
    free(is_collapsed);
    free(is_root);
    return res;
}


int main() {

    int n, m, q;
    if (scanf("%d%d%d", &n, &m, &q) != 3) return 1;

    int** bridges = (int**) malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++) {
        bridges[i] = (int*) malloc(sizeof(int) * 2);
    }
    int* collapse = (int*) malloc(sizeof(int) * q);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &bridges[i][0], &bridges[i][1]);
    }

    for (int i = 0; i < q; i++) {
        scanf("%d", &collapse[i]);
    }

    int* res = solver(bridges, collapse, n, m, q);
    for (int i = 0; i <= q; i++) {
        printf("%d\n", res[i]);
    }

    for (int i = 0; i < m; i++) free(bridges[i]);
    free(bridges);
    free(collapse);
    return 0;
}