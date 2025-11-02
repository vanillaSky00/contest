## Leftis tree
| Operation          | Time Complexity                                              | Explanation                                                                                                                                                                           |
| ------------------ | ------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **`insert()`**     | **O(log n)** (worst-case via `meld`) | *Lazy insert* by creating a single-node leftist tree, then `meld` it with the existing. tree.                                                                                |
| **`deleteMin()`**  | **O(log n)**                                                 | Remove the root, then `meld` its left and right subtrees (each already a leftist tree).                                                                                               |
| **`meld()`**       | **O(log n)**                                                 | Merge two leftist trees by comparing roots. Recurse along the right path. After merging, ensure the **leftist property** by swapping children if needed so that `shortest(left) ≥ shortest(right)`. |
| **`initialize()`** | **O(n)**                                                     | Build a leftist tree from `n` nodes using a bottom-up method: pairwise `meld` nodes in a FIFO queue n + 2 * (1×n/2 + 2×n/4 + 3×n/8 + … ≈ 2n). Total cost = O(n).                                   |

Initialize() steps :<br>
Place all n single-node trees in a queue.<br>
Repeatedly meld pairs (top down + bottom up)<br>
Cost series: n + 2(1·n/2 + 2·n/4 + 3·n/8 + …) ≈ 5n = O(n).<br>

### terms

- Extended Binary Tree: <br>
A binary tree where every null pointer is replaced with an external node.

- Shortest(x): <br>
The length of the shortest path from node x to an external node (null child). Sometimes called the null path length (NPL).

- `NPL(x) = 1 + min(NPL(left(x)), NPL(right(x)))`, with `NPL(NULL) = 0`.

- HBLT (Height-Biased Leftist Tree): <br>
`sortest(left) ≥ shortest(right)`
Ensures the right path is the shortest, giving `O(log n)` height.


- WBLT (Weight-Biased Leftist Tree): <br>
Balances based on weight instead of height,
where `weight(v)` = number of nodes in the subtree rooted at v.

### 3 properties
- The rightmost path is always the shortest path to a null node. Its length is `O(log n)`. Annotate this path as $shortest(x)$.
- Consider to meet the first node in $shortest(x)$, this situation is like a complete binary tree with the node on tree is the last one, then total node will be $2^{i - 1}$.

- If the last node at layer $k$ on the path of $shortest(x)$ then it is bounded by $2^{k - 1}$, then $k = log{(x + 1)}$ this explains $O(logn)$ for meld, insert, delete.


## DFS
topological sort
dfs properties
dfs 4 edges type
connected components
strongly connected
dfs spanning tree
articulation point: a child of vertex v cannot return to any ancestor of v via other path

classification of edges:
https://www.youtube.com/watch?v=2g0TJH_ZJYI
remember that DFS output a forest not a tree so
1 tree edge: normal edge from ancestor to descent
2 forward edge: not on DFS tree, but an edge on the origin graph
3 back edge: edge to ancestor (already explore node within same tree)
4 cross edge: edge to another tree

## BFS

if using n * n adjMatrix then the time complexity is O(n2)
if using adjList then the time complexity is O(V+E)

## Minimum Cost Spanning Tree
- 3 * 3 types we need to be aware of:
weighted/ unweighted
connected/ unconnected
directed/ undirected

- properties:
|E| = |V| - 1

here we only consider weighted, connectd, and undirected graph, and in these 3 assumption, we can apply Kruskal or Prim algorithm

kruskal:
we min heap or leftis, initialize with O(e), remove each time O(loge), eloge
or with sorting edge and select: O(eloge)

check if in cycle with DSU: 
initialize O(n)
at most 2e finds and n - 1 unions: ~O(e+n)

for each iteration time for unionfind is less than that of get a min edge


## DSU
we can make `parent` set to idx or -1 when initialzation, `rank`

lemma5.6  Tarjan and Van leeuwen 
collapsing rule 

Time complexity for u unions and f finds
naive DSU: $O(nf)$
weight/ heigth rule DSU: $O(n + flog{f})$
weight/ height rule + collapsing rule DSU: $O(n + f)$