const std = @import("std");

fn DefaultCompareFn(T: type) *const fn(T, T) i8 {
    const DC = struct {
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
    const dc = DC{};
    return dc.func;
}

test "Fn" {
    const func = DefaultCompareFn(i8);
    std.debug.print("{}\n", .{func(5, 6)});
}
