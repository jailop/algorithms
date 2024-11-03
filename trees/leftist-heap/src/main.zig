//! LEFTIST TREE IMPLEMENTATION
//!
//! This implementation is based on:
//!
//! Brass, P. (2008). Advanced Data Structures. Cambridge University Press.
//! pp. 227-234

const std = @import("std");
const HeapTree = @import("heaptree.zig").HeapTree;

pub fn main() !void {
    // Setting a memory allocator
    const allocator = std.heap.page_allocator;
    // Creating a new HeapTree
    var tree = HeapTree(u8){.allocator = allocator};
    defer tree.deinit();
    // Data sample
    const keys = [_]u8{
        15, 27, 22, 35, 40, 13, 9,
        10, 5, 6, 3,
        31, 16, 42, 33, 37, 41, 21,
        30, 32, 29, 23, 8, 11, 28,
    };
    // Displaying the data sample as the input 
    std.debug.print("\n----- INPUT -----\n", .{});
    for (keys) |key| {
        std.debug.print("{} ", .{key});
    }
    std.debug.print("\n", .{});
    // Tree visualization
    std.debug.print("\n----- TREE -----\n", .{});
    tree.insertMany(&keys);
    tree.print();
    // Getting sorted the sample data
    std.debug.print("\n----- OUTPUT -----\n", .{});
    while (tree.deleteMin()) |key| {
        std.debug.print("{d} ", .{key});
    }
    std.debug.print("\n", .{});
}
