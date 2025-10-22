## Overall

## Approach


### 0 Naive Brute Force
Time complexity:
Space complexity:


### 1 Branch and Bound
The algorithm depends on efficient estimation of the lower and upper bounds of regions/branches of the search space. If no bounds are available, then the algorithm degenerates to an exhaustive search.
"efficient estimation" heuristic approach??
Goal: find the x that maximize f(x), for solution candidate set S, we called search space or feasible region
we only talk about minimization cause g(x) = -f(x) then we solve the maximize problem 


Time complexity:
Space complexity:


### 2 DP
Time complexity:
Space complexity:


## Note
> The TSP cannot be solved exactly using greedy methods, hence any greedy method is a heuristic. By definition, therefore, DP will always find a better (or, no worse) feasible solution than a greedy heuristic will, for any instance of the TSP.

https://stackoverflow.com/questions/54534089/greedy-approach-vs-dynamic-programming-in-travelling-salesman