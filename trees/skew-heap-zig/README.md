# Skew Heap - Generic implementation in Zig

This implementation contains a generic version for skew heaps.

Example:

```zig
const Point = struct {
    x: f32,
    y: f32,
    fn dist(self: @This()) f32 {
        return std.math.sqrt(self.x * self.x + self.y * self.y);
    }
};

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
```
