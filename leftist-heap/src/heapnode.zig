//! LEFTIST TREE IMPLEMENTATION
//!
//! This implementation is based on:
//!
//! Brass, P. (2008). Advanced Data Structures. Cambridge University Press.
//! pp. 227-234
//!
//! (c) 2024 - Jaime Lopez <https://github.com/jailop>

const std = @import("std");

/// Represents a node for the leftist tree.
pub fn HeapNode(T: type) type {
    return struct {
        key : T,
        left: ?*@This() = null,
        right: ?*@This() = null,
        
        // A pretty print function to show the tree in horizontal positon.
        pub fn print(self: *@This(), level: usize) void {
                if (self.left) |leftNode| {
                    leftNode.print(level + 1);
                }
                // Based on the deepth level, spaces are inserted before showing
                // the node information
                for (1..level + 1) |i| {
                    var spaces = "    ";
                    if (i == level) {
                        spaces = "|---";
                    }
                    std.debug.print("{s}", .{spaces});
                }
                std.debug.print("{}\n", .{self.key});
                if (self.right) |rightNode| {
                    rightNode.print(level + 1);
                }
        }

    };
}


test "Heap Node" {
    const node = HeapNode(u8){.key = 5};
    try std.testing.expectEqual(node.key, 5);
}