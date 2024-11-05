//! LEFTIST TREE IMPLEMENTATION
//!
//! This implementation is based on:
//!
//! Brass, P. (2008). Advanced Data Structures. Cambridge University Press.
//! pp. 227-234

const HeapNode = @import("heapnode.zig").HeapNode;
const heapMerge = @import("heapmerge.zig").heapMerge;

pub fn heapInsert(T: type, root: *HeapNode(T), node: *HeapNode(T)) *HeapNode(T) {
    return heapMerge(T, root, node).?;
}
