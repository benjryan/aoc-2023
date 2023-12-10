#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#define SIZE 140

enum TileType {
    VERTICAL,
    HORIZONTAL,
    NORTH_EAST,
    NORTH_WEST,
    SOUTH_EAST,
    SOUTH_WEST,
    GROUND,
    START,

    TILE_COUNT
};

char tiles[TILE_COUNT] = { '|', '-', 'L', 'J', 'F', '7', '.', 'S' };
char field[SIZE][SIZE];

struct Coord {
    int x;
    int y;
};

struct Tile {
    Coord coord;
    TileType type;
    Coord prev;
    int dst;
};

struct Visited {
    int dst;
};

bool is_connected(Tile t0, Tile t1)
{
    if (t0.type == GROUND || t1.type == GROUND)
        return false;

    if (t0.coord.x == t1.coord.x && t0.coord.y == t1.coord.y)
        return false;

    if (abs(t0.coord.x - t1.coord.x) + abs(t0.coord.y - t1.coord.y) > 1)
        return false;

    if (t0.coord.x < t1.coord.x) {
        // t0 is left
        if (t0.type == VERTICAL || t0.type == NORTH_WEST || t0.type == SOUTH_WEST)
            return false;
        if (t1.type == VERTICAL || t1.type == NORTH_EAST || t1.type == SOUTH_EAST)
            return false;
    } else if (t0.coord.x > t1.coord.x) {
        // t0 is right
        if (t0.type == VERTICAL || t0.type == NORTH_EAST || t0.type == SOUTH_EAST)
            return false;
        if (t1.type == VERTICAL || t1.type == NORTH_WEST || t1.type == SOUTH_WEST)
            return false;
    } else if (t0.coord.y < t1.coord.y) {
        // t0 is above
        if (t0.type == HORIZONTAL || t0.type == NORTH_EAST || t0.type == NORTH_WEST)
            return false;
        if (t1.type == HORIZONTAL || t1.type == SOUTH_EAST || t1.type == SOUTH_WEST)
            return false;
    } else if (t0.coord.y > t1.coord.y) {
        // t0 is below
        if (t0.type == HORIZONTAL || t0.type == SOUTH_EAST || t0.type == SOUTH_WEST)
            return false;
        if (t1.type == HORIZONTAL || t1.type == NORTH_EAST || t1.type == NORTH_WEST)
            return false;
    }

    return true;
}

bool is_valid(int x, int y)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        return false;

    return true;
}

TileType find_type(char c)
{
    for (int i = 0; i < TILE_COUNT; ++i) {
        if (tiles[i] == c)
            return (TileType)i;
    }

    return TILE_COUNT;
}

void get_neighbors(Tile tile, Tile* neighbors)
{
    int x, y;
    x = tile.coord.x;
    y = tile.coord.y - 1;
    if (is_valid(x, y)) {
        Tile up = { { x, y }, find_type(field[y][x]), tile.coord, tile.dst + 1 };
        if (is_connected(tile, up)) {
            neighbors[0] = up;
        }
    }

    x = tile.coord.x;
    y = tile.coord.y + 1;
    if (is_valid(x, y)) {
        Tile down = { { x, y }, find_type(field[y][x]), tile.coord, tile.dst + 1 };
        if (is_connected(tile, down)) {
            neighbors[1] = down;
        }
    }
    x = tile.coord.x - 1;
    y = tile.coord.y;
    if (is_valid(x, y)) {
        Tile left = { { x, y }, find_type(field[y][x]), tile.coord, tile.dst + 1 };
        if (is_connected(tile, left)) {
            neighbors[2] = left;
        }
    }
    x = tile.coord.x + 1;
    y = tile.coord.y;
    if (is_valid(x, y)) {
        Tile right = { { x, y }, find_type(field[y][x]), tile.coord, tile.dst + 1 };
        if (is_connected(tile, right)) {
            neighbors[3] = right;
        }
    }
}

int main()
{
    FILE* fp = fopen("input.txt", "r");
    char line[1024];
    int line_count = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
        strncpy(field[line_count++], line, SIZE);

    Tile start;
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            char c = field[y][x];
            if (c == tiles[START]) {
                start = { { x, y }, START, { -1, -1 } };
                goto found_start;
            }
        }
    }

found_start:
    int visited[SIZE][SIZE];
    memset(visited, -1, sizeof(int)*SIZE*SIZE);
    Tile queue[1024] = {0};
    int queue_count = 0;
    queue[queue_count++] = start;
    while (queue_count > 0)
    {
        Tile tile = queue[0];
        queue_count--;
        memcpy(queue, queue + 1, sizeof(Tile) * queue_count);
        Tile neighbors[4];
        for (int i = 0; i < 4; ++i)
            neighbors[i] = { { -1, -1 }, TILE_COUNT, { -1, -1 }, -1 };
        get_neighbors(tile, neighbors);
        for (int i = 0; i < 4; ++i) {
            Tile neighbor = neighbors[i];
            if (neighbor.type == TILE_COUNT) 
                continue;

            int v = visited[neighbor.coord.y][neighbor.coord.x];
            if (v != -1 && v <= neighbor.dst)
                continue;

            visited[neighbor.coord.y][neighbor.coord.x] = neighbor.dst;
            queue[queue_count++] = neighbor;
        }
    }

    int largest = -1;
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            int v = visited[y][x];
            if (v > largest)
                largest = v;

            if (v == -1)
                printf("____ ");
            else if (v > 999)
                printf("%d ", v);
            else if (v > 99)
                printf(" %d ", v);
            else if (v > 9)
                printf("  %d ", v);
            else
                printf("   %d ", v);
        }
        printf("\n");
    }

    printf("largest: %d\n", largest);
}
