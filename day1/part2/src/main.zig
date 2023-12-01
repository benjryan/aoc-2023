const std = @import("std");
const io = std.io;

const input = @embedFile("input.txt");

const tokens = [_] [] const u8 {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

fn getDigit(s: []const u8) i32 {
    var tokenIndex: i32 = -1;
    for (tokens, 0..) |t, i| {
        if (std.mem.eql(u8, t, s)) {
            tokenIndex = @intCast(i);
            break;
        }
    }

    if (tokenIndex > 9)
        tokenIndex -= 10;

    return tokenIndex;
}

pub fn main() !void {
    var sum: i32 = 0;
    const newLine = [_]u8{ 13, 10 };
    var lineIter = std.mem.tokenize(u8, input, &newLine);
    while (lineIter.next()) |line| {
        var firstIdx: i32 = 1000;
        var lastIdx: i32 = -1000;
        var first: []const u8 = undefined;
        var last: []const u8 = undefined;
        for (tokens) |t| {
            var idx = std.mem.indexOf(u8, line, t);
            if (idx) |i| {
                if (i < firstIdx) {
                    firstIdx = @intCast(i);
                    first = t;
                }
            }
            idx = std.mem.lastIndexOf(u8, line, t);
            if (idx) |i| {
                if (i > lastIdx) {
                    lastIdx = @intCast(i);
                    last = t;
                }
            }
        }

        const n = 10 * getDigit(first) + getDigit(last);
        sum += n;
    }

    std.debug.print("{}", .{ sum });
}

