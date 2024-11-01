const std = @import("std");

const Pair = struct {
    a: [64]u8,
    b: [64]u8,
    freq: u32,
    pub fn set(x: []const u8, y: []const u8, accu: u32) Pair {
        var self : ?Pair = undefined;
        std.mem.copyForwards(u8, self.?.a, x);
        std.mem.copyForwards(u8, self.?.b, y);
        self.?.freq = accu;
        return self.?;
    }
    pub fn add(self: *Pair, accu: u32) void {
        self.freq += accu;
    }
    pub fn equal(self: Pair, x: []const u8, y: []const u8) bool {
        return std.mem.eql(u8, &(self.a), x) and std.mem.eql(u8, &(self.b), y);
    }
};

fn updatePair(pairs: *std.ArrayList(Pair), x: []const u8, y: []const u8, accu: u32) !void {
    for (0..pairs.items.len) | i | {
        if (pairs.items[i].equal(x, y)) {
            pairs.items[i].add(accu);
            return;
        }
    }
    try pairs.*.append(Pair.set(x, y, accu)); 
}

fn getPairs(allocator: std.mem.Allocator, vocab: std.StringHashMap(u32)) !std.ArrayList(Pair) {
    var it = vocab.iterator();
    var pairs = std.ArrayList(Pair).init(allocator);
    _ = &pairs;
    while (it.next()) | entry | {
        var symbols = std.mem.splitScalar(u8, entry.key_ptr.*, ' ');
        while (symbols.next()) | sym1 | {
            const following = symbols.peek();
            if (following) | sym2 | {
                try updatePair(&pairs, sym1, sym2, entry.value_ptr.*);    
            }
        }
    }
}

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

//fn mergeVocab(allocator: std.mem.Allocator, pair: []const u8, v_in: std.StringHashMap(u32)) !std.StringHashMap(u32) {
//    var v_out = std.StringHashMap(u32).init(allocator);
//    var escaped_pair = allocator.alloc(u8, pair.len + 1);
//    defer allocator.free(escaped_pair);
//    var idx_target = 0;
//    for (pair) | c | {
//        if (c == ' ') {
//            escaped_pair[idx_target] = '\\';
//            idx_target += 1;
//        }
//        escaped_pair[idx_target] = c;
//        idx_target += 1;
//    }
//
//    return v_out;
//}

fn printStringMap(sm: std.StringHashMap(u32)) void {
    var it = sm.iterator();
    while (it.next()) | entry | {
        std.debug.print("{s}: {d}\n", .{entry.key_ptr.*, entry.value_ptr.*});
    }
}

test "BPE" {
    const allocator = std.testing.allocator;
    var vocab = std.StringHashMap(u32).init(allocator);
    defer vocab.deinit();

    try vocab.put("l o w </w>", 5);
    try vocab.put("l o w e r </w>", 2);
    try vocab.put("n e w e s t </w>", 6);
    try vocab.put("w i d e s t </w>", 3);
    
    const num_merges = 10;
    for (0..num_merges) |_| {
        var pairs = try getPairs(allocator, vocab);
        defer pairs.deinit();
    }
}
