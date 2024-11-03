//! LEFTIST TREE IMPLEMENTATION
//!
//! This implementation is based on:
//!
//! Brass, P. (2008). Advanced Data Structures. Cambridge University Press.
//! pp. 227-234
//!
//! (c) 2024 - Jaime Lopez <https://github.com/jailop>

const std = @import("std");
const HeapNode = @import("heapnode.zig").HeapNode;

/// Merges to trees designating the node with the less value a the parent. It
/// performs the same operation for every children that has two childreen too.
pub fn heapMerge(T: type, node1: ?*HeapNode(T), node2: ?*HeapNode(T))
    ?*HeapNode(T)
{
    // If one node is null, the merge operation cannot be performed. Therefore,
    // the other node is returned.
    if (node1 == null) {
        return node2;
    }
    if (node2 == null) {
         return node1;
    }
    // Proceding with the merge operation.
    var root : ?*HeapNode(T) = null;
    var tmp1 : ?*HeapNode(T) = null;
    var tmp2 : ?*HeapNode(T) = null;
    var tmp3 : ?*HeapNode(T) = null;
    // Getting the node with the minimum value to the left
    if (node1.?.key > node2.?.key) {
        std.mem.swap(HeapNode(T), node1.?, node2.?);
    }
    // The new root is the node with the minimum value
    root = node1;
    // Temporal references
    tmp1 = node1;
    tmp2 = tmp1.?.right;
    tmp3 = node2;
    while (tmp2 != null and tmp3 != null) {
        // Loops while the right on the left and the right nodes are not null
        if (tmp1) |tmp1_| {
            // If the left node exists, puts its left children on the right.
            // The reference to the right children is already saved on `tmp2`
            tmp1_.right = tmp1_.left;
        }
        // Swapping the get the node with the minimum value on the left 
        if (tmp2.?.key > tmp3.?.key) {
            std.mem.swap(HeapNode(T), tmp2.?, tmp3.?);
        }
        // The left of the left now is `tmp2`
        if (tmp1) |tmp1_| {
            tmp1_.left = tmp2;
        }
        // Going first on the left and next on the right
        tmp1 = tmp2;
        tmp2 = tmp2.?.right;
    }
    if (tmp2) |_tmp2| {
        if (tmp1) |tmp1_| {
            tmp1_.right = _tmp2;
        }
    } else {
        if (tmp1) |tmp1_| {
            tmp1_.right = tmp3;
        }
    }
    return root;
}

// Experimental feature. It is not working yet.
pub fn heapMergeRecursive(T: type, node1: ?*HeapNode(T), node2: ?*HeapNode(T))
    ?*HeapNode(T)
{
    // If one node is null, the merge operation cannot be performed. Therefore,
    // the other node is returned.
    if (node1 == null) {
        return node2;
    }
    // if (node2 == null) {
    //     return node1;
    // }
    if (node1) |node1_| {
        node1_.right = heapMergeRecursive(T, node1_.right, node2);
    }
    if (node1.?.left == null) {
        if (node1) |node1_| {
            const tmp = node1_.left;
            node1_.left = node1_.right;
            node1_.right = tmp;
        }
    }
//    else {
//        const left = node1.?.left;
//        const right = node1.?.right;
//        if (left.?.key < right.?.key) {
//            node1.?.right = left;
//            node1.?.left = right;
//        }
//    }
    return node1;
}
