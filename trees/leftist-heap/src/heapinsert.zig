//! LEFTIST TREE IMPLEMENTATION
//!
//! This implementation is based on:
//!
//! Brass, P. (2008). Advanced Data Structures. Cambridge University Press.
//! pp. 227-234

const HeapNode = @import("heapnode.zig").HeapNode;

/// Creates a new node for the argument `key` and inserts that node
/// into the tree. In case it is needed, this function updates the
/// root.
pub fn heapInsert(T: type, root: *HeapNode(T), node: *HeapNode(T)) *HeapNode(T) {
    if (node.key < root.key) {
        // The new value is the minimum in the tree.
        // As a consequence, its node is designed as
        // the new root. The former root is colocated on
        // the left of the new one.
        node.left = root;
        return node;
    } else {
        var current = root;
        // Going down by the right until finding a node which value
        // is greater the argument `key`
        while (current.right) |right| {
            if (right.key > node.key) {
                break;
            }
            // Left and right are swapped.  The new current is
            // set on the previous right, that now it is left.
            current.right = current.left;
            current.left = right;
            current = right;
        }
        // The new node is inserted between current and its child on
        // the right
        node.left = current.right;
        current.right = node;
        // root remains the same
        return root;
    }
}
