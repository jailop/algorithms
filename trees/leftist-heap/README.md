# Leftist Heap Tree

The leftist heap tree supports operations `findMin` in $\mathit{O}(1)$ time and
`insert`, `merge`, and `delete` in $\mathit{O}(log_n)$.  The leaftist tree has
the property that in each node, the shortest path on the left is at least as
long as on the right side. It doesn't matter if the tree is unbalanced, but
always on the right, a heap with $n$ elements contains a path of length at most
$log(n + 1)$.

With the sample data included in the program, the output is:

```
15 27 22 35 40 13 9 10 5 6 3 31 16 42 33 37 41 21 30 32 29 23 8 11 28 

----- TREE -----
                |---42
            |---37
        |---21
            |---32
    |---16
            |---31
        |---23
|---11
    |---28
3
    |---6
                |---33
            |---30
        |---8
|---5
                    |---27
                |---22
                    |---35
            |---15
                |---40
        |---13
            |---29
    |---9
        |---10
            |---41

----- OUTPUT -----
3 5 6 8 9 10 11 13 15 16 21 22 23 27 28 29 30 31 32 33 35 37 40 41 42 
```
