/// Cross index search algorithm
/// See README.md for the problem description.
/// Solution using a binary search algorithm.

const std = @import("std");

const CrossIndexError = error {
    ArraysWithDifferentSize,
    InvalidIndices,
    InvalidArrays,
};

/// Look for indices where the search criteria is true.
///
/// Arguments:
///
///     T : type of data paramenters
///     res : an array list to return results
///     x : first array
///     y : second array
///     left : left index position to start the search
///     right : right index position to end the search
///
/// Assumptions:
///     
///     left < right
///     x.len == y.len
///     y[0] < x[0]
///     y[y.len - 1] > x[x.len - 1]
///
/// Return:
///
///     void or error
pub fn crossindex(T: type, res: *std.ArrayList(u64), x: []T, y: []T, left: u64, right: u64) !void {
    // Checking error conditions
    if (left >= right) return CrossIndexError.ArraysWithDifferentSize;
    if (x.len != y.len) return CrossIndexError.InvalidIndices;
    // if (x[0] >= y[0]) return CrossIndexError.InvalidArrays;
    // if (y[y.len - 1] <= x[x.len - 1]) return CrossIndexError.InvalidArrays;
    // Computing middle index
    const mid = left + (right - left) / 2;
    // Evaluating search condition
    if ((y[mid] <= x[mid]) and (y[mid + 1] >= x[mid + 1])) {
        try res.append(mid);
    }
    // Recursing search on the left and right sides
    if (mid - left >= 1) {
        try crossindex(T, res, x, y, left, mid);
        try crossindex(T, res, x, y, mid + 1, right);
    }
}

test "Crossindex with one result" {
    var x = [_]i32{ 0, 2, 4, 5, 6, 7,  8, 10};
    var y = [_]i32{-2, 0, 2, 4, 7, 8, 10, 12};
    var res = std.ArrayList(u64).init(std.testing.allocator);
    defer res.deinit();
    try crossindex(i32, &res, &x, &y, 0, x.len - 1);
    const response = [_]u64{3};
    try std.testing.expect(std.mem.eql(u64, res.items, &response));
}

test "Crossindex with more than one result" {
    var x = [_]f32{ 0.0, 1.0, 4.0, 5.0, 6.0, 7.0,  8.0, 10.0};
    var y = [_]f32{-2.0, 1.5, 2.0, 4.0, 7.0, 8.0, 10.0, 12.0};
    var res = std.ArrayList(u64).init(std.testing.allocator);
    defer res.deinit();
    try crossindex(f32, &res, &x, &y, 0, x.len - 1);
    const response = [_]u64{3, 0};
    try std.testing.expect(std.mem.eql(u64, res.items, &response));
}

//test "Crossindex error with arrays of diffent size" {
//    var x = [_]i32{ 0, 2, 4, 5, 6, 7,  8, 10};
//    var y = [_]i32{-2, 0, 2, 4, 7, 8, 10};
//    var res = std.ArrayList(u64).init(std.testing.allocator);
//    defer res.deinit();
//    const response = try crossindex(i32, &res, &x, &y, 0, x.len - 1);
//    try std.testing.expect(response == CrossIndexError.ArraysWithDifferentSize);
//}
