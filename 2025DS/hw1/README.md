


```
static inline void link(int a, int b) { R[a] = b; L[b] = a;}
```
make a and b neighbors.
- Insert: cut a gap and link twice.
- Delete: bypass a node with link(L[k], R[k]).
- Move: delete + insert.


```
link(new, R[HEAD]);
link(HEAD, new);
```