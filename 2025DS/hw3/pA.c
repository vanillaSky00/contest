#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// reverse the time line technique
typedef struct DSU {
    int* parent;
    int* rank;
    int** groups;
} DSU;

int find(DSU* dsu, int x) {
    return (dsu->parent[x] == x) ? x : (dsu->parent[x] = find(dsu, x));
}

void union_find(DSU* dsu, int x, int y) {
    x = find(dsu, x);
    y = find(dsu, y);
    if (x == y) return;
    
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
}



void solver(int** bridges, int* collapse, int n, int m, int q) {
    DSU* dsu = (DSU*) malloc(sizeof(DSU));
    dsu->parent = (int*) malloc(sizeof(int) * (n + 1));
    dsu->rank = (int*) calloc(n + 1,sizeof(int));

    for (int i = 0; i <= n; i++) dsu->parent[i] = i;

    int e = 200000 < (n * (n-1))/2 ? 200000 : (n * (n-1))/2;
    bool* seen = (bool*) calloc(e, sizeof(bool));
    for (int i = 0; i < q; i++) seen[collapse[i]] = true;
    

    for (int i = 0; i < q; i++) {
        if (collapse[i] == false) {
            union_find(dsu, bridges[i][0], bridges[i][1]);
        }
    }

    // TODO
    print_groups(dsu);

    // reverse: add from last
    for (int i = q - 1; i >= 0; i++) {
        union_find(dsu, bridges[i][0], bridges[i][1]);
        print_groups(dsu);
    }

    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
    free(seen);
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

    solver(bridges, collapse, n, m, q);

    for (int i = 0; i < m; i++) free(bridges[i]);
    free(bridges);
    free(collapse);
    return 0;
}