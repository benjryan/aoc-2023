#include <stdio.h>

int main()
{
    int time[4] = { 54, 70, 82, 75 };
    int dst[4] = { 239, 1142, 1295, 1253 };
    int wins[4] = { 0 };

    for (int race = 0; race < 4; race++) {
        int max_time = time[race];
        int max_dst = dst[race];

        for (int hold = 0; hold < max_time; ++hold) {
            int remaining_time = max_time - hold;
            int dst_travelled = remaining_time * hold;
            if (dst_travelled > max_dst)
                wins[race]++;
        }
    }

    printf("answer: %d\n", wins[0] * wins[1] * wins[2] * wins[3]);
}
