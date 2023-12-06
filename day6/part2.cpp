#include <stdio.h>

int main()
{
    size_t max_time = 54708275;
    size_t max_dst = 239114212951253;
    size_t wins = 0;

    for (size_t hold = 0; hold < max_time; ++hold) {
        size_t remaining_time = max_time - hold;
        size_t dst_travelled = remaining_time * hold;
        if (dst_travelled > max_dst)
            wins++;
    }

    printf("answer: %llu\n", wins);
}
