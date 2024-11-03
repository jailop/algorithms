# Leftist Heap Tree

The leftist heap tree supports operations `findMin` on $\mathit{O}(1)$ time and
`insert`, `merge`, and `delete` in $\mathit{O}(log_n)$.  The leaftist tree has
the property that in each node, the shortest path on the left is at least as
long as on the right side. It doesn't matter if the tree is unbalanced, but
always on the right, a heap with $n$ elements contains a path of length at most
$log(n + 1)$.
