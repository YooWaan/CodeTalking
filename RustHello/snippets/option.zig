const std = @import("std");

const Value = struct {
    num: u32,
    ref: ?*const Value,
};

pub fn main() void {
    const v1: Value = Value{
        .num = 1,
        .ref = null,
    };

    const v2 = Value{
        .num = 2,
        .ref = &v1,
    };

    std.debug.print("v1={}\n", .{v1});
    std.debug.print("v2={}\n", .{v2});

    if (v1.ref) |val| {
        std.debug.print("V1.Ref={} {*}p\n", .{val.num, &val});
    } else {
        std.debug.print("V1.Num={} {*}p\n", .{v1.num, &v1});
    }

    if (v2.ref) |val| {
        std.debug.print("V2.Ref={} {*}p\n", .{val.num, &val});
    } else {
        std.debug.print("V2.Num={} {*}p\n", .{v2.num, &v2});
    }
}
