#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// use topological sort to detect cycle

// dependencies[0] from, dependencies[1] to
static int solve(int** dependencies, int d, int n) {
    // use topologicalSort
    int* inDegrees = (int*) calloc(n, sizeof(int));
    int* adjSize = (int*) calloc(n, sizeof(int));

    for (int i = 0; i < d; i++) {
        inDegrees[dependencies[i][1]]++;
        adjSize[dependencies[i][0]]++;
    }
    
    int** adj = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        adj[i] = (int*) malloc(sizeof(int) * adjSize[i]);
        adjSize[i] = 0; // reset
    }

    for (int i = 0; i < d; i++) {
        int from = dependencies[i][0];
        adj[from][adjSize[from]++] = dependencies[i][1];
    }

    int* q = (int*) malloc(sizeof(int) * n);
    int front = 0, rear = 0;
    for (int i = 0; i < n; i++) {
        if (inDegrees[i] == 0) q[rear++] = i;
    }

    int index = 0;
    //int* ordering = (int*) malloc(sizeof(int) * n);
    while (rear > front) {
        int u = q[front++];
        index++;
        //ordering[index++] = u;
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            inDegrees[v]--;
            if (inDegrees[v] == 0) {
                q[rear++] = v;
            }
        } 
    }

    free(inDegrees);
    free(adjSize);
    free(q);
    //free(ordering);
    for (int i = 0; i < n; i++) free(adj[i]); 
    free(adj);

    return index == n;// at least one cycle 
}

int main() {
    int n, d;
    scanf("%d%d", &n, &d);

    int** dependencies = (int**) malloc(sizeof(int*) * d);
    for (int i = 0; i < d; i++) {
        dependencies[i] = (int*) malloc(sizeof(int) * 2);
    }

    for (int i = 0; i < d; i++) {
        scanf("%d%d", &dependencies[i][0], &dependencies[i][1]);
    }

    bool res = solve(dependencies, d, n);

    for (int i = 0; i < d; i++) free(dependencies[i]);
    free(dependencies);

    if (!res) printf("1\n");
    else printf("0\n");
    return 0;
}


