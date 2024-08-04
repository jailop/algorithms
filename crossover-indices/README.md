# Crossover Indices

Given a set of points $\{(x_j, y_i) | (x_{i} < x_{i + 1}) \wedge (y_{i} < y_{i + 1}) \wedge (y_0 < x_0) \wedge (y_n > x_n), i \in \{0, \dots, n - 1\}\}$.

Find the crossover indexes $\in \{0, 1, \dots, n - 1\}$ such that $y_i \leq x_i \wedge y_{i + 1} > x_{i + 1}$.

At least one index exists given that at least $y_0 < x_0$ and $y_n > x_n$.

To check solution implementation using binary search:

```sh
zig test crossoverindex.zig
```
