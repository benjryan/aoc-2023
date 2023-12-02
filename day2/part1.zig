const std = @import("std");
const input = @embedFile("input.txt");

pub fn main() !void {
    var it = std.mem.tokenize(u8, input, "\r\n");
    var sum: i32 = 0;
    while (it.next()) |line| {
        var start = std.mem.indexOf(u8, line, " ") orelse 0; start += 1;
        var end = std.mem.indexOf(u8, line, ":") orelse 0;
        var game_id = std.fmt.parseInt(i32, line[start..end], 10) catch 0;
        var set_it = std.mem.tokenize(u8, line[(end + 1)..], ";");
        loop: {
            while (set_it.next()) |set| {
                var action_it = std.mem.tokenize(u8, set, ",");
                while (action_it.next()) |raw_action| {
                    var action = std.mem.trim(u8, raw_action, " ");
                    if (std.mem.indexOf(u8, action, " ")) |space| {
                        var count = try std.fmt.parseInt(i32, action[0..space], 10);
                        var color = action[space+1..];

                        if (std.mem.eql(u8, color, "red")) {
                            if (count > 12) {
                                break :loop;
                            }
                        } else if (std.mem.eql(u8, color, "green")) {
                            if (count > 13) {
                                break :loop;
                            }
                        } else {
                            if (count > 14) {
                                break :loop;
                            }
                        }
                    }
                }
            }

            sum += game_id;
        }
    }

    std.debug.print("{d}\n", .{ sum });
}
