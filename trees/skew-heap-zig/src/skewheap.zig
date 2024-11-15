//! Skew Heap
//! A generic implementation
//!
//! (c) 2024 Jaime Lopez <https://github.com/jailop>

const std = @import("std");

// Heap can ordered by minimum or by maximum
pub const HeapType = enum {
    MinHeap,
    MaxHeap,
};

pub const HeapError = error {
    EmptyHeap,
};

// This function can be used for comparable scalars.
fn DefaultCompareFn(T: type) *const fn(T, T) i8 {
    const DF = struct {
        func: *const fn(T, T) i8 = @This().defaultCompareFn,
        fn defaultCompareFn(value1: T, value2: T) i8 {
            if (value1 > value2) {
                return 1;
            } else if (value1 < value2) {
                return -1;
            }
            return 0;
        }
    };
    const df = DF{};
    return df.func;
}

pub fn SkewHeap(T: type) type {
    return struct {
        const Self = @This();

        pub const Node = struct {
            data: T,
            left: ?*Node = null,
            right: ?*Node = null,
        };

        root: ?*Node = null,
        heap_type: HeapType,
        compareFn: *const fn(T, T) i8,
        allocator: std.mem.Allocator,

        pub fn init(allocator: std.mem.Allocator, heap_type: HeapType, comptime compareFn: ?*const fn(T, T) i8) Self {
            if (compareFn == null) {
                return Self{
                    .allocator = allocator,
                    .heap_type = heap_type,
                    .compareFn = DefaultCompareFn(T), 
                };
            } else {
                return Self{
                    .allocator = allocator,
                    .heap_type = heap_type,
                    .compareFn = compareFn.?, 
                };
            }
        }

        pub fn deinit(self: *Self) void {
            self.deleteNode(self.root);
        }

        // This is the delete function for a binary tree. It
        // is provided to clean up the allocated memory.
        fn deleteNode(self: *Self, node: ?*Self.Node) void {
            if (node) |nd| {
                self.deleteNode(nd.left);
                self.deleteNode(nd.right);
                self.allocator.destroy(nd);
            }
        }

        pub fn removeRoot(self: *Self) !T {
            if (self.root) |nd| {
                const value = nd.data;
                self.root = self.merge(nd.right, nd.left);
                self.allocator.destroy(nd);
                return value;
            }
            return HeapError.EmptyHeap;
        }

        pub fn peek(self: Self) !T {
            if (self.root) |nd| {
                return nd.data;
            }
            return HeapError.EmptyHeap;
        }

        fn merge(self: Self, node1: ?*Self.Node,
            node2: ?*Self.Node) ?*Self.Node {
            if (node1 == null) {
                return node2;
            }
            if (node2 == null) {
                return node1;
            }
            var nd1 = node1.?;
            var nd2 = node2.?;

            const comp = self.compareFn(nd1.data, nd2.data) == 1;
            const cond = if (self.heap_type == HeapType.MinHeap) comp else !comp;
            if (cond) {
                const tmp = nd1;
                nd1 = nd2;
                nd2 = tmp;
            }
            const tmp = nd1.right;
            nd1.right = nd1.left;
            nd1.left = tmp;
            nd1.left = self.merge(nd2, nd1.left);
            return nd1;
        }

        pub fn insert(self: *Self, value: T) !*Self.Node {
            const node = try self.allocator.create(Self.Node);
            node.* = Self.Node{.data = value};
            self.root = self.merge(self.root, node);
            return node;
        }

        fn print(self: Self) void {
            self._print(self.root);
            std.debug.print("\n", .{});
        }

        fn _print(self: Self, node: ?*Self.Node) void {
            if (node) |nd| {
                std.debug.print("(", .{});
                self._print(nd.left);
                std.debug.print(" {} ", .{nd.data});
                self._print(nd.right);
                std.debug.print(")", .{});
            }
        }
    };
}

test "Skew Tree" {
    const allocator = std.testing.allocator;
    var heap = SkewHeap(u8).init(allocator, HeapType.MinHeap, null);
    defer heap.deinit();
    const x = [_]u8{0, 5, 3, 6, 2, 7, 9, 4, 8, 1};
    for (x) |value| {
        _ = try heap.insert(value);
    }
    for (0..10) |i| {
        try std.testing.expect(try heap.removeRoot() == i);
    }
}

// For Testing
const Point = struct {
    x: f32,
    y: f32,
    fn dist(self: @This()) f32 {
        return std.math.sqrt(self.x * self.x + self.y * self.y);
    }
};

// For Testing
fn compPoint(point1: Point, point2: Point) i8 {
    const d1 = point1.dist();
    const d2 = point2.dist();
    if (d1 < d2) {
        return -1;
    } else if (d1 > d2) {
        return 1;
    }
    return 0;
}

test "Struc Test" {
    const allocator = std.testing.allocator;
    var heap = SkewHeap(Point).init(allocator, HeapType.MaxHeap, compPoint);
    defer heap.deinit();
    const points = [_]Point{
        .{.x=2.0, .y=3.0}, .{.x=2.9, .y=3.3},
        .{.x=4.1, .y=-5.2}, .{.x=-1.1, .y=1.9},
        .{.x=1.5, .y=-2.1}, .{.x=1.3, .y=4.5},
    };
    for (points) |point| {
        _ = try heap.insert(point);
    }
    var prev = std.math.inf(f32);
    for (0..points.len) |_| {
        const p = try heap.removeRoot();
        const d = p.dist();
        // The next value shuld be lower than the previous one
        try std.testing.expect(d < prev);
        prev = d; 
    }
}
