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
const heapMerge = @import("heapmerge.zig").heapMerge;

/// Represents a generate leftist tree. It maintains at the root the 
/// minimum value.
pub fn HeapTree(T: type) type {
    return struct {
        root: ?*HeapNode(T) = null,
        allocator: std.mem.Allocator,

        /// Given that the tree's root contains the minimum value, this
        /// functions just returns the value of the root node.
        pub fn findMin(self: @This()) ?T{
            return if (self.root) |_root| _root.key else null;
        }

        /// Indicates if the tree is empty or not.
        fn isEmpty(self: @This()) bool {
            return if (self.root) |_| false else true;
        }

        /// Creates a new node for the argument `key` and inserts that node
        /// into the tree.
        fn insert(self: *@This(), key: T) !void {
            // Creating a new node
            var node = try self.allocator.create(HeapNode(T));
            node.* = HeapNode(T){.key = key};
            // Looking for the position in the tree of the new node
            if (self.root) |root| {
                // Already existis a node as root
                if (key < root.key) {
                    // The new value is the minimum in the tree.
                    // As a consequence, its node is designed as
                    // the new root. The former root is colocated on
                    // the left of the new one.
                    node.left = self.root;
                    self.root = node;
                } else {
                    var current = root;
                    // Going down by the right until finding a node which value
                    // is greater the argument `key`
                    while (current.right) |right| {
                        if (right.key < key) {
                            // Left and right are swapped.  The new current is
                            // set on the previous right, that now it is left.
                            current.right = current.left;
                            current.left = right;
                            current = right;
                        } else {
                            break;
                        }
                    }
                    // The new node is inserted between current and its child on
                    // the right
                    node.left = current.right;
                    current.right = node;
                }
            } else {
                // The tree is empty, so the new node is designated as the root.
                self.root = node;
            }
        }

        /// Auxiliar function to insert multiple elements in one call.
        /// It uses a loop to call `insert` many times as need based on the
        /// number of items received.
        pub fn insertMany(self: *@This(), keys: []const T) void {
            for (keys) |key| {
                self.insert(key) catch {
                    std.debug.print("Key {} could not be inserted\n", .{key});
                };
            }
        }

        /// Returns memory used by the tree. It calls the `freeNode` function
        /// passing the root node as the argument.
        pub fn deinit(self: *@This()) void {
            if (self.root) |root| {
                self.freeNode(root);
                self.root = null;
            }
        }

        /// This tree uses dynamic memoryt to allocate nodes. In corresponce, it
        /// has this deallocation function that recursivelly frees the memory
        /// used by the tree's nodes.
        fn freeNode(self: *@This(), node: *HeapNode(T)) void {
            // Deallocating memory on the left
            if (node.left) |left| {
                self.freeNode(left);
            }
            // Deallocating memory on the right
            if (node.right) |right| {
                self.freeNode(right);
            }
            // Deallocating the current node
            self.allocator.destroy(node);
        }

        /// Removes the current root node and call
        /// the merging process between its children to designate
        /// the new root, that will be the one containing the
        /// lesser key. This function has an auxiliary function that
        /// that works at node level.
        pub fn deleteMin(self: *@This()) ?T {
            var key : ?T = null;
            if (self.root) |_root| {
                // Keeping the key before destroying the current root.
                key = _root.key;
                // Asigning a new root. The previous one has been destroyed
                self.root = self._deleteMin(_root);
            } 
            return key;
        }

        /// Auxiliary function responsible of merging the root's children.
        /// It is also responsible to deallocate the asigned memory to the root.
        fn _deleteMin(self: *@This(), node: ?*HeapNode(T)) ?*HeapNode(T) {
            var newParent : ?*HeapNode(T) = null;
            if (node) |_node| {
                // Computing the new root
                newParent = heapMerge(T, _node.left, _node.right);
                // Destroying the current root
                self.allocator.destroy(_node); 
            }
            return newParent;
        }

        // Prints the tree starting by the root.
        // The argument `0` represents the first level. It is an auxiliary value
        // to draw a tree on the screen.
        pub fn print(self: @This()) void {
            if (self.root) |root| {
                root.print(0);
            } {
                std.debug.print("{s}\n", .{"Empty tree."});
            }
        }
    };
}

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    var tree = HeapTree(u8){.allocator = allocator};
    defer tree.deinit();
    const keys = [_]u8{
        30, 32, 29, 23, 8, 11, 28,
        10, 5, 6, 3,
        31, 16, 42, 33, 37, 41, 21,
        15, 27, 22, 35, 40, 13, 9,
    };
    
    std.debug.print("\n----- INPUT -----\n", .{});
    for (keys) |key| {
        std.debug.print("{} ", .{key});
    }
    std.debug.print("\n", .{});
    
    std.debug.print("\n----- TREE -----\n", .{});
    tree.insertMany(&keys);
    tree.print();

    std.debug.print("\n----- OUTPUT -----\n", .{});
    while (tree.deleteMin()) |key| {
        std.debug.print("{d} ", .{key});
    }
    std.debug.print("\n", .{});
}
