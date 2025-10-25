

## Kahn's algorithm
https://en.wikipedia.org/wiki/Topological_sorting

## Notes for pB
0 Use reset `adjSize[i] = 0` to track the number again
1 forget to initialize with `calloc(n, sizeof(e))` rather than `malloc` and then increment the element
2 size of topo res check with number of nodes not number of dependency
