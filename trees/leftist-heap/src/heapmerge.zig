//! LEFTIST TREE IMPLEMENTATION
//!
//! This implementation is based on:
//!
//! Brass, P. (2008). Advanced Data Structures. Cambridge University Press.
//! pp. 227-234

const std = @import("std");
const HeapNode = @import("heapnode.zig").HeapNode;

/// Merges to trees designating the node with the less value a the parent. It
/// performs the same operation for every children that has two childreen too.
pub fn heapMerge(T: type, node1: ?*HeapNode(T), node2: ?*HeapNode(T))
    ?*HeapNode(T)
{
    // If one node is null, the merge operation cannot be performed. Therefore,
    // the other node is returned.
    if (node1 == null or node2 == null) {
        return if (node1 == null) node2 else node1;
    }
    if (node1.?.key > node2.?.key) {
        return heapMerge(T, node2, node1);
    }
    const n1 = node1.?;  // We're sure node1 is not null
    n1.right = heapMerge(T, n1.right, node2);
    if (n1.left == null) {
        const tmp = n1.left;
        n1.left = n1.right;
        n1.right = tmp;
        n1.s = 1;
        return n1;
    }
    if (n1.right.?.s < n1.left.?.s) {
        const tmp = n1.left;
        n1.left = n1.right;
        n1.right = tmp;
    }
    n1.s = n1.right.?.s;
    return n1;
}
