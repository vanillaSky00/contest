## Overall
This repository is my collection of learning notes from NCKU CSIE Data Structures.
pB is Prefix-Sum + Harmonic Trick for Floor Division Problems
pD is Linked List Maintenance Using Arrays


## Prefix-Sum + Harmonic Trick for Floor Division Problems
These are hints you can bucket values by ranges and use prefix sums to reduce complexity.
```
floor(a / t)
a % t
“largest multiple of t ≤ a”
A loop like for t=K..max(a)
```

Naïve `O(N·M)` is too slow. (1 <= N, M <= 1e6)

![formula1](https://latex.codecogs.com/svg.latex?\max_{t\geq%20K}\;\sum_{i=1}^{N}\left\lfloor\frac{a_i}{t}\right\rfloor\cdot%20t)

$N = number of squads$ <br>
$a_i = size of squad i$ <br>
$t = chosen team size (𝑡≥𝐾)$ <br>


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

![formula2](https://latex.codecogs.com/svg.latex?\sum_{t=K}^{M}\frac{M}{t}\;=\;M\cdot%20H_M\;\approx\;M\log%20M)


$M = max(a_i​)$ <br>
$H_M = the 𝑀-th harmonic number$ <br>



## Linked List Maintenance Using Arrays
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