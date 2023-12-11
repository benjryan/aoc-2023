#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Galaxy {
    int x;
    int y;
};

char image[1024][1024] = {0};
int expanded_cols[128] = {0};
int expanded_col_count = 0;
int expanded_rows[128] = {0};
int expanded_row_count = 0;

int main()
{
    FILE* fp = fopen("input.txt", "r");
    char line[1024];
    int line_count = 0;
    int width = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (width == 0)
            width = strlen(line) - 1;
        strncpy(image[line_count++], line, width);

        bool empty = true;
        int x = 0;
        while (true) {
            char c = image[line_count - 1][x++];
            if (c == 0)
                break;

            if (c != '.') {
                empty = false;
                break;
            }
        }
        
        if (empty)
            expanded_rows[expanded_row_count++] = line_count - 1;
    }

    {
        int x = 0;
        while (x < width) {
            bool empty = true;
            for (int y = 0; y < line_count; ++y)
            {
                char c = image[y][x];
                if (c != '.') {
                    empty = false;
                    break;
                }
            }

            if (empty)
                expanded_cols[expanded_col_count++] = x;

            x++;
        }
    }

    Galaxy galaxies[1024];
    int galaxy_count = 0;
    for (int y = 0; y < line_count; ++y) {
        for (int x = 0; x < width; ++x) {
            char c = image[y][x];
            if (c == '#')
                galaxies[galaxy_count++] = { x, y };
        }
    }

    size_t sum = 0;
    for (int i = 0; i < galaxy_count; ++i) {
        for (int j = 0; j < galaxy_count; ++j) {
            Galaxy a = galaxies[i];
            Galaxy b = galaxies[j];
            int exp_col = 0;
            for (int start = std::min(a.x, b.x); start < std::max(a.x, b.x); ++start) {
                for (int exp = 0; exp < expanded_col_count; ++exp) {
                    if (expanded_cols[exp] == start) {
                        exp_col++;
                        break;
                    }
                }
            }
            size_t dst_x = abs(a.x - b.x) + 999999 * exp_col;

            int exp_row = 0;
            for (int start = std::min(a.y, b.y); start < std::max(a.y, b.y); ++start) {
                for (int exp = 0; exp < expanded_row_count; ++exp) {
                    if (expanded_rows[exp] == start) {
                        exp_row++;
                        break;
                    }
                }
            }
            size_t dst_y = abs(a.y - b.y) + 999999 * exp_row;
            sum += dst_x + dst_y;
        }
    }
    printf("sum: %llu\n", sum/2);
}
