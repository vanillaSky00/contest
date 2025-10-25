
# Detect a cycle
$O(V+E)$ for time and space complexity <br>

We can use topological sort to detect with
https://en.wikipedia.org/wiki/Topological_sorting

## Kahn's algorithm (BFS)
Need a queue and start with node with `inDegree = 0`

## DFS approach
| State | Meaning                                 |
| ----- | --------------------------------------- |
| `0`   | Not visited yet                         |
| `1`   | Visiting (currently in recursion stack) |
| `2`   | Done (fully processed)                  |
```c
bool dfs(int u, int* state, int** adj, int* adjSize, int* stack, int* top) {
    state[u] = 1; // visiting

    for (int i = 0; i < adjSize[u]; i++) {
        int v = adj[u][i];
        if (state[v] == 1) return true;      // found a back edge → cycle
        if (state[v] == 0 && dfs(v, state, adj, adjSize, stack, top)) 
            return true;
    }

    state[u] = 2;                // done
    stack[(*top)++] = u;         // push to topo order
    return false;
}
```

| Method                     | Technique                                | Detects cycle? | How                                                                                  |
| -------------------------- | ---------------------------------------- | -------------- | ------------------------------------------------------------------------------------ |
| **Kahn’s algorithm (BFS)** | Use indegrees + queue                    | ✅              | If you can’t pop all `n` nodes (some remain with indegree > 0) → cycle               |
| **DFS-based (recursive)**  | Postorder traversal with recursion stack | ✅              | If you find a **back edge** (an edge to a node still in the recursion stack) → cycle |


## Notes for pB
0 Use reset `adjSize[i] = 0` to track the number again
1 forget to initialize with `calloc(n, sizeof(e))` rather than `malloc` and then increment the element
2 size of topo res check with number of nodes not number of dependency
