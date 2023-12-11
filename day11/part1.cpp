#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Galaxy {
    int x;
    int y;
};

char image[1024][1024] = {0};

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
        
        if (empty) {
            strncpy(image[line_count++], line, width);
        }
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

            if (empty) {
                for (int y = 0; y < line_count; ++y) {
                    memcpy(&image[y][x + 2], &image[y][x + 1], width - x);
                    image[y][x + 1] = '.';
                }
                width++;
                x++;
            }

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

    int sum = 0;
    for (int i = 0; i < galaxy_count; ++i) {
        for (int j = 0; j < galaxy_count; ++j) {
            Galaxy a = galaxies[i];
            Galaxy b = galaxies[j];
            int dst = abs(a.x - b.x) + abs(a.y - b.y);
            sum += dst;
        }
    }
    printf("sum: %d\n", sum/2);
}
