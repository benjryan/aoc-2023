const std = @import("std");
const input = @embedFile("input.txt");

pub fn main() !void {
    var ull = std.mem.indexOf(u8, input, "\n") orelse 0;
    if (ull == 0)
        return;

    ull += 1;
    var ll: i32 = @intCast(ull);

    const offsets = [_]i32{ 
        -ll - 1, -ll, -ll + 1,
        -1, 1,
        ll - 1, ll, ll + 1,
    };

    var sum: i32 = 0;
    var line_count = @divFloor(input.len, ull);
    for (0..line_count) |line_id| {
        var start = line_id * ull;
        var end = start + ull;
        var line = input[start..end];
        var number_str: [32]u8 = undefined;
        var digit_count: u32 = 0;
        var found_symbol = false;
        for (line, 0..) |c, i| {
            if (std.ascii.isDigit(c)) {
                number_str[digit_count] = c;
                digit_count += 1;

                // just read to the end of the number if we've already found
                // the symbol
                if (found_symbol)
                    continue;

                // adjacency test
                for (offsets) |offset| {
                    var adj_idx: i32 = @as(i32, @intCast(start + i)) + offset;
                    if (adj_idx < 0 or adj_idx >= input.len)
                        continue;

                    var rel_c = input[@intCast(adj_idx)];
                    if (!std.ascii.isAlphanumeric(rel_c) and rel_c != '.' and rel_c != '\r' and rel_c != '\n') {
                        // symbol!
                        found_symbol = true;
                        break;
                    }
                }
            } else {
                if (digit_count > 0 and found_symbol) {
                    // add number to sum
                    var number = std.fmt.parseInt(i32, number_str[0..digit_count], 10) catch 0;
                    //std.debug.print("engine part: {d}\n", .{ number });
                    sum += number;
                }

                // reset values
                digit_count = 0;
                found_symbol = false;
            }
        }
    }

    std.debug.print("{d}\n", .{ sum });
}
