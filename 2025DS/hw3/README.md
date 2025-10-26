# Overall
The problems are
- `pA.c` : Number of Alliance with DSU
- `pB.c` : Detect a cycle, return true or false
- `pC.c` : BFS for a maze
- `pD.c` : MST grows from one node
- `pE.c` : Hash table


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

<br>

| Method                     | Technique                                | Detects cycle? | How                                                                                  |
| -------------------------- | ---------------------------------------- | -------------- | ------------------------------------------------------------------------------------ |
| **Kahn’s algorithm (BFS)** | Use indegrees + queue                    | ✅              | If you can’t pop all `n` nodes (some remain with indegree > 0) → cycle               |
| **DFS-based (recursive)**  | Postorder traversal with recursion stack | ✅              | If you find a **back edge** (an edge to a node still in the recursion stack) → cycle |

<br>
<br>

# Minimum Spanning Tree (MST)
In brief, Prim is better when a graph is dynamic, growing from one node.

| Situation                                    | Explanation                                                                                     |
| -------------------------------------------- | ----------------------------------------------------------------------------------------------- |
| **Graph is dynamic**                         | You don’t know all edges in advance (e.g., discovered on-the-fly from a network or API).        |
| **Graph is dense**                           | A graph where the number of edges is close to the maximum possible number of edges. Prim’s with a priority queue (binary heap or Fibonacci heap) can handle O(E log V) efficiently. |
| **Graph stored as adjacency list or matrix** | Prim’s can directly use these structures without building a global edge list.                   |

<br>

| Aspect                | Kruskal       | Prim                                   |
| :-------------------- | :------------ | :------------------------------------- |
| Needs all edges known | ✅ Yes        | ❌ No                                  |
| Works with            | Edge list     | Adjacency list / matrix                |
| Good for              | Sparse graphs | Dense or dynamically discovered graphs |
| Typical complexity    | O(E log E)    | O(E log V) with heap                   |
| Cycles                | need DSU      | a set of visited vertex                |

<br>

Note for Prims:
- Disconnected graphs: The loop over all start builds an MSF (minimum spanning forest), do it by each groups. If you need a single MST, ensure the graph is connected.
- Dense graphs: Replace the heap with an array of bestWeight[v] + linear scan (`O(V^2)`)—often faster in practice for dense inputs.
- Fancy heaps: Fibonacci heap gives theoretical `O(E + V log V)` but has big constants. But binary heap is preferred in contests/production.

<br>

Prim + PQ is both efficient and clean, and it won’t add cycles as long as you keep the visited check.


# Hash Table
Why not hash table:
| Approach                     | Feasibility                                                                     | Notes |
| ---------------------------- | ------------------------------------------------------------------------------- | ----- |
| **Array / bool visited[id]** | ❌ Impossible if IDs are large (wastes memory)                                   |       |
| **`id % MAX_NODES` trick**   | ❌ Collisions, incorrect behavior                                                |       |
| **Bloom filter**             | ⚠️ Saves memory, but may skip valid vertices (false positives ⇒ incomplete MST) |       |
| **Hashmap (`uthash`)**       | ✅ Exact, fast, and memory-efficient for 100 000 entries                         |       |
| **ID compression + array**   | ✅ Also good, but more code; hashmap does the same automatically                 |       |

<br>
<br>

| Concept              | Description                                                       |
| -------------------- | ----------------------------------------------------------------- |
| Table                | fixed array of buckets of size = power of two ≥ 2× expected count |
| Hash function        | multiply by a big odd constant (`Knuth’s constant`)               |
| Collision resolution | probe `i = (i + 1) & (cap-1)` until empty or key found            |

- With capacity ≈ 200 000 and 100 000 inserts → expected O(1) lookups, < 1 MB memory.
- If your IDs can be negative, this still works (hash casts to unsigned safely).
- If you later need to rehash, you can easily extend hs_add to rebuild the table.


## With `uthash` (header-only):
- Average lookup / insert: O(1)
- Memory per entry: ≈ 32–40 bytes
- For 100 000 nodes → 3–4 MB total, perfectly fine even on embedded Linux.
- No need to know the ID range in advance.

## Notes for pB
- Use reset `adjSize[i] = 0` to track the number again.
- Forget to initialize with `calloc(n, sizeof(e))` rather than `malloc` and then increment the element.
- Size of topo result should be in same as the number of nodes not that of dependency.

