```
This repository is my collection of learning notes from NCKU CSIE Data Structures.
pB is Prefix-Sum + Harmonic Trick for Floor Division Problems
pD is Linked List Maintenance Using Arrays
```

### Prefix-Sum + Harmonic Trick for Floor Division Problems
These are hints you can bucket values by ranges and use prefix sums to reduce complexity.
```
floor(a / t)
a % t
“largest multiple of t ≤ a”
A loop like for t=K..max(a)
```

Naïve `O(N·M)` is too slow. (1 <= N, M <= 1e6)
$$
\max_{t \geq K} \; \sum_{i=1}^{N} \left\lfloor \frac{a_i}{t} \right\rfloor \cdot t

N = number of squads
a_i = size of squad i
t = chosen team size (𝑡≥𝐾)
$$

```
freq[x] = how many squads of size x
prefCnt[x] = Σ_{v ≤ x} freq[v]
cnt = prefCnt[R] - prefCnt[L-1];
```

```
for (int t = K; t <= maxNum; t++) {
    long long ans = 0;
    for (int j = 1; j * t <= maxNum; j++) {
        int L = j * t;
        int R = min((j+1)*t - 1, maxNum); // boundary 
        long long cnt = prefCnt[R] - prefCnt[L-1];
        ans += 1LL * j * t * cnt; // each contributes j * t
    }
    best = max(best, ans);
}
```
Time Complexity : `MlogM`
$$
\sum_{t=K}^{M} \frac{M}{t} \;=\; M \cdot H_M \;\approx\; M \log M

M = max(a_i​)
H_M = the 𝑀-th harmonic number
$$


### Linked List Maintenance Using Arrays
Use arrays to maintain neighbors in linked list
```
L[i] = id of the node left of i
R[i] = id of the node right of i
val[i] = value stored at node i
```

Make neighbors in order of : a <-> b 
```
static inline void link(int a, int b) { R[a] = b; L[b] = a;}
```

Operation
```
Insert at head / tail
Insert before / after node k
Delete node k
Move node k to head / tail
```
make a and b neighbors.
- Insert: cut a gap and link twice.
- Delete: bypass a node with link(L[k], R[k]).
- Move: delete + insert.

Time Complexity : `O(1)`

Other resources: Luogu P1996 (static linked list)

### Is static array
Safe: no dynamic allocation bugs.
Fast: predictable O(1).