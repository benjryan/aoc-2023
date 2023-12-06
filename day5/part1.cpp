#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

enum MapType {
    SEED_TO_SOIL,
    SOIL_TO_FERTILIZER,
    FERTILIZER_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMPERATURE,
    TEMPERATURE_TO_HUMIDITY,
    HUMIDITY_TO_LOCATION,

    MAPTYPE_COUNT
};

struct Range {
    size_t dest;
    size_t src;
    size_t len;
};

int main()
{
    FILE* fp = fopen("input.txt", "r");
    char line[1024];
    std::vector<Range> maps[MAPTYPE_COUNT];
    std::vector<size_t> seeds;
    MapType line_type = MAPTYPE_COUNT;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char* heading = strtok(line, ":");
        if (strcmp(heading, "seeds") == 0) {
            line_type = MAPTYPE_COUNT;
            char* remaining = strtok(NULL, ":");
            char* next_number = strtok(remaining + 1, " ");
            while (next_number != NULL) {
                size_t seed;
                if (sscanf(next_number, "%llu", &seed) == 1)
                    seeds.push_back(seed);

                next_number = strtok(NULL, " ");
            }
        } else if (strcmp(heading, "seed-to-soil map") == 0) {
            line_type = SEED_TO_SOIL;
        } else if (strcmp(heading, "soil-to-fertilizer map") == 0) {
            line_type = SOIL_TO_FERTILIZER;
        } else if (strcmp(heading, "fertilizer-to-water map") == 0) {
            line_type = FERTILIZER_TO_WATER;
        } else if (strcmp(heading, "water-to-light map") == 0) {
            line_type = WATER_TO_LIGHT;
        } else if (strcmp(heading, "light-to-temperature map") == 0) {
            line_type = LIGHT_TO_TEMPERATURE;
        } else if (strcmp(heading, "temperature-to-humidity map") == 0) {
            line_type = TEMPERATURE_TO_HUMIDITY;
        } else if (strcmp(heading, "humidity-to-location map") == 0) {
            line_type = HUMIDITY_TO_LOCATION;
        } else {
            size_t dest, src, len;
            if (sscanf(line, "%llu %llu %llu", &dest, &src, &len) == 3) {
                Range range = { dest, src, len };
                maps[line_type].push_back(range);
            }
        }
    }

    size_t min_seed = SIZE_MAX;
    for (int i = 0; i < seeds.size(); ++i) {
        size_t seed = seeds[i];
        for (int j = 0; j < MAPTYPE_COUNT; ++j) {
            std::vector<Range> map = maps[j];
            bool found = false;
            for (int k = 0; k < map.size(); k++) {
                Range range = map[k];
                if (seed >= range.src && seed < range.src + range.len) {
                    seed = range.dest + (seed - range.src);
                    found = true;
                    break;
                }
            }
        }

        if (seed < min_seed)
            min_seed = seed;
    }

    printf("result: %llu\n", min_seed);
}
