#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DSU {
    int *parent;
    int *rank;
    int *size;
    int *id;       // id[x] = current DSU index representing the real x
    int next_id;   // next free DSU index to use when someone "moves"
} DSU;

int find(DSU *dsu, int x) {
    return dsu->parent[x] == x ? x : (dsu->parent[x] = find(dsu, dsu->parent[x]));
}

bool union_find(DSU *dsu, int x, int y) {
    x = find(dsu, x);
    y = find(dsu, y);
    if (x == y) return false;

    if (dsu->rank[x] > dsu->rank[y]) {
        dsu->parent[y] = x;
        dsu->size[x] += dsu->size[y];
    }
    else if (dsu->rank[x] < dsu->rank[y]) {
        dsu->parent[x] = y;
        dsu->size[y] += dsu->size[x];
    }
    else {
        dsu->parent[x] = y;
        dsu->rank[y]++;
        dsu->size[y] += dsu->size[x];
    }
    return true;
}

void move_to(DSU *dsu, int x, int y) {
    int old_node = dsu->id[x];
    int old_root = find(dsu, old_node);
    int new_root = find(dsu, dsu->id[y]);
    
    if (old_root == new_root) return;

    dsu->size[old_root]--;
    
    int nx = dsu->next_id++;
    dsu->parent[nx] = nx;
    dsu->rank[nx] = 0;
    dsu->size[nx] = 1;
    dsu->id[x] = nx;

    union_find(dsu, nx, dsu->id[y]); // here that is why dsu->id[nx] would out of bound
}

int get_group_size(DSU *dsu, int x) {
    return dsu->size[find(dsu, dsu->id[x])];
}

DSU *create_dsu(int N, int Q) {
    int max_node = N + Q + 5;

    DSU *dsu = (DSU*) malloc(sizeof(DSU));

    dsu->parent = (int*) malloc((max_node + 1) * sizeof(int));
    dsu->rank   = (int*) calloc(max_node + 1, sizeof(int));
    dsu->size   = (int*) calloc(max_node + 1, sizeof(int));
    dsu->id     = (int*) malloc((N + 1) * sizeof(int));

    for (int i = 1; i <= max_node; i++) {
        dsu->parent[i] = i;
    }

    for (int i = 1; i <= N; i++) {
        dsu->size[i] = 1;
        dsu->id[i] = i;
    }

    // nodes from N+1..maxNodes initially unused
    dsu->next_id = N + 1;
    return dsu;
}

int main(void) {
    int N, Q;
    scanf("%d%d", &N, &Q);
    DSU *dsu = create_dsu(N, Q);

    while (Q-- > 0) {
        int cmd;
        int x, y;
        scanf("%d", &cmd);
        if (cmd == 1) {
            scanf("%d%d", &x, &y);
            union_find(dsu, dsu->id[x], dsu->id[y]);
        }
        else if (cmd == 2) {
            scanf("%d%d", &x, &y);
            move_to(dsu, x, y);
        }
        else if (cmd == 3) {
            scanf("%d", &x);
            int s = get_group_size(dsu, x);
            printf("%d\n", s);
        }
        else {
            printf("Invalid arguments.\n");
        }
    }

    free(dsu->parent);
    free(dsu->rank);
    free(dsu->size);
    free(dsu->id);
    free(dsu);
    return 0;
} 