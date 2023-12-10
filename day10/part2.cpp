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
bool loop[140][140] = {0};

char large_tiles[TILE_COUNT][9] = {
    { '.', '|', '.',
      '.', '|', '.',
      '.', '|', '.' },

    { '.', '.', '.',
      '-', '-', '-',
      '.', '.', '.' },

    { '.', '|', '.',
      '.', 'L', '-',
      '.', '.', '.' },

    { '.', '|', '.',
      '-', 'J', '.',
      '.', '.', '.' },

    { '.', '.', '.',
      '.', 'F', '-',
      '.', '|', '.' },

    { '.', '.', '.',
      '-', '7', '.',
      '.', '|', '.' },

    { '.', '.', '.',
      '.', '.', '.',
      '.', '.', '.' },

    //{ 'S', 'S', 'S',
    //  'S', 'S', 'S',
    //  'S', 'S', 'S' },
    // this is only correct for my input data
    { '.', '.', '.',
      '.', 'F', '-',
      '.', '|', '.' },
};

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
                start = { { x, y }, START, { -1, -1 }, 0 };
                goto found_start;
            }
        }
    }

found_start:
    {
        Tile visited[SIZE][SIZE] = {0};
        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE; ++x) {
                visited[y][x].dst = -1;
            }
        }
        Tile queue[1024] = {0};
        int queue_count = 0;
        queue[queue_count++] = start;
        visited[start.coord.y][start.coord.x] = start;
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

                Tile v = visited[neighbor.coord.y][neighbor.coord.x];
                if (v.dst != -1 && v.dst <= neighbor.dst)
                    continue;

                visited[neighbor.coord.y][neighbor.coord.x] = neighbor;
                queue[queue_count++] = neighbor;
            }
        }

        Tile largest = {0};
        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE; ++x) {
                Tile v = visited[y][x];
                if (v.dst > largest.dst)
                    largest = v;

                //if (v.dst == -1)
                //    printf("____ ");
                //else if (v.dst > 999)
                //    printf("%d ", v);
                //else if (v.dst > 99)
                //    printf(" %d ", v);
                //else if (v.dst > 9)
                //    printf("  %d ", v);
                //else
                //    printf("   %d ", v);
            }
            //printf("\n");
        }

        // find the actual loop tiles
        loop[largest.coord.y][largest.coord.x] = true;
        Tile neighbors[4];
        for (int i = 0; i < 4; ++i)
            neighbors[i] = { { -1, -1 }, TILE_COUNT, { -1, -1 }, -1 };
        get_neighbors(largest, neighbors);
        for (int i = 0; i < 4; ++i) {
            Tile n = neighbors[i];
            if (n.dst == -1)
                continue;

            Tile v = visited[n.coord.y][n.coord.x];
            if (v.dst == largest.dst - 1) {
                loop[v.coord.y][v.coord.x] = true;
                Coord next = v.prev;
                while (true) {
                    loop[next.y][next.x] = true;
                    Tile t = visited[next.y][next.x];
                    if (next.x == start.coord.x && next.y == start.coord.y)
                        break;

                    next = t.prev;
                }
            }
        }
    }

    //for (int y = 0; y < SIZE; ++y) {
    //    for (int x = 0; x < SIZE; ++x) {
    //        if (!loop[y][x]) {
    //            printf(".");
    //        } else {
    //            printf("#");
    //            //char buffer[2] = {0};
    //            //buffer[0] = field[y][x];
    //            //printf(buffer);
    //        }
    //    }
    //    printf("\n");
    //}

    char new_loop[SIZE*3][SIZE*3] = {0};
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            TileType type = GROUND;
            if (loop[y][x]) {
                type = find_type(field[y][x]);
            }
            char* large = large_tiles[type];
            for (int dy = 0; dy < 3; ++dy) {
                for (int dx = 0; dx < 3; ++dx) {
                    int ny = y*3 + dy;
                    int nx = x*3 + dx;
                    new_loop[ny][nx] = large[dy * 3 + dx];
                }
            }
        }
    }

    int inner_count = 0;
    Tile* visited = (Tile*)malloc(sizeof(Tile) * (SIZE*3) * (SIZE*3));
    Tile* queue = (Tile*)malloc(sizeof(Tile) * 1024 * 1024);
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            if (loop[y][x])
                continue;

            for (int vy = 0; vy < SIZE*3; ++vy) {
                for (int vx = 0; vx < SIZE*3; ++vx) {
                    visited[vy*SIZE*3+vx].dst = -1;
                }
            }

            Tile start;
            start.coord = { x * 3 + 1, y * 3 + 1 };
            start.dst = x + y;

            int queue_count = 0;
            queue[queue_count++] = start;
            visited[start.coord.y*SIZE*3+start.coord.x] = start;

            while (queue_count > 0) {
                Tile tile = queue[0];
                if (tile.dst == 0)
                    goto outer;

                queue_count--;
                memcpy(queue, queue + 1, sizeof(Tile) * queue_count);

                Coord coords[4] = { 
                    { tile.coord.x, tile.coord.y - 1 },
                    { tile.coord.x, tile.coord.y + 1 },
                    { tile.coord.x - 1, tile.coord.y },
                    { tile.coord.x + 1, tile.coord.y }
                };

                for (int i = 0; i < 4; ++i) {
                    Coord coord = coords[i];
                    if (coord.x < 0 || coord.x >= SIZE*3 ||
                        coord.y < 0 || coord.y >= SIZE*3)
                        continue;

                    if (new_loop[coord.y][coord.x] != '.')
                        continue;

                    int dst = coord.x + coord.y;
                    if (dst == 0)
                        goto outer;

                    Tile neighbor;
                    neighbor.coord = coord;
                    neighbor.dst = dst;

                    Tile v = visited[coord.y*SIZE*3+coord.x];
                    if (v.dst != -1)// && v.dst <= dst)
                        continue;

                    visited[coord.y*SIZE*3+coord.x] = neighbor;
                    int insert_id = queue_count;
                    for (int q = 0; q < queue_count; ++q) {
                        if (dst <= queue[q].dst) {
                            insert_id = q;
                            break;
                        }
                    }
                    
                    if (insert_id < queue_count)
                        memcpy(queue + insert_id + 1, queue + insert_id, sizeof(Tile) * (queue_count - insert_id));
                    queue[insert_id] = neighbor;
                    queue_count++;
                }
            }

            inner_count++;
outer:
            int z = 0;
        }
    }

    printf("inner: %d\n", inner_count);

    //for (int y = 0; y < SIZE*3; ++y) {
    //    for (int x = 0; x < SIZE*3; ++x) {
    //        if (new_loop[y][x] == '.')
    //            printf(" ");
    //        else
    //            printf("%c", new_loop[y][x]);
    //    }
    //    printf("\n");
    //}
}
