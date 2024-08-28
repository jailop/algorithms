const std = @import("std");

fn getStats(allocator: std.mem.Allocator, vocab: std.StringHashMap(u32)) !std.StringHashMap(u32) {
    var pairs = std.StringHashMap(u32).init(allocator);
    var it = vocab.iterator();
    while (it.next()) | entry | {
        var symbols = std.mem.splitScalar(u8, entry.key_ptr.*, ' ');
        while (symbols.next()) | sym1 | {
            const following = symbols.peek();
            if (following) | sym2 | {
                const pair = try std.fmt.allocPrint(allocator, "{s} {s}", .{sym1, sym2});
                const ent = pairs.getEntry(pair);
                if (ent) | en | {
                    en.value_ptr.* += entry.value_ptr.*;
                    allocator.free(pair);
                } else {
                    try pairs.put(pair, entry.value_ptr.*);
                }
            }
        }
    }
    return pairs;
}

fn mergeVocab(allocator: std.mem.Allocator, pair: []const u8, v_in: std.StringHashMap(u32)) !std.StringHashMap(u32) {
    var v_out = std.StringHashMap(u32).init(allocator);
    var escaped_pair = allocator.alloc(u8, pair.len + 1);
    defer allocator.free(escaped_pair);
    var idx_target = 0;
    for (pair) | c | {
        if (c == ' ') {
            escaped_pair[idx_target] = '\\';
            idx_target += 1;
        }
        escaped_pair[idx_target] = c;
        idx_target += 1;
    }
    const pattern = std.fmt.allocPrint(allocator, "(?<!\\S){s}(?!\\S)", .{escaped_pair});

    return v_out;
}

fn printStringMap(sm: std.StringHashMap(u32)) void {
    var it = sm.iterator();
    while (it.next()) | entry | {
        std.debug.print("{s}: {d}\n", .{entry.key_ptr.*, entry.value_ptr.*});
    }
}

test "BPE" {
    const allocator = std.testing.allocator;
    var vocab = std.StringHashMap(u32).init(std.heap.page_allocator);
    defer vocab.deinit();

    try vocab.put("l o w </w>", 5);
    try vocab.put("l o w e r </w>", 2);
    try vocab.put("n e w e s t </w>", 6);
    try vocab.put("w i d e s t </w>", 3);
    
    const num_merges = 10;
    for (0..num_merges) |_| {
        var pairs = try getStats(allocator, vocab);
        defer {
            var it = pairs.iterator();
            while (it.next()) | entry | {
                allocator.free(entry.key_ptr.*);
            }
            pairs.deinit();
        }
        printStringMap(pairs);
    }
}
