const std = @import("std");
const io = std.io;

const input = @embedFile("input.txt");

pub fn main() !void {
    var sum: i32 = 0;
    const split = [_]u8{ 13, 10 };
    var iter = std.mem.tokenize(u8, input, &split);
    while (iter.next()) |line| {
        var digits: [2]u8 = undefined;
        var i: usize = 0;

        // iterate
        while (i < line.len) : (i += 1) {
            const c = line[i];
            if (c < '0' or c > '9')
                continue;
            digits[0] = c;
            break;
        }

        // reverse iterate
        i = line.len - 1;
        while (i >= 0) : (i -= 1) {
            const c = line[i];
            if (c < '0' or c > '9')
                continue;
            digits[1] = c;
            break;
        }

        if (digits[0] == 0)
            continue;

        const n = std.fmt.parseInt(i32, digits[0..2], 10) catch 0;
        sum += n;
    }

    std.debug.print("{}", .{ sum });
}

