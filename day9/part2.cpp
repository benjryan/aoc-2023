#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE* fp = fopen("input.txt", "r");
    char line[1024];
    int sum = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char* n = strtok(line, " ");
        int numbers[128][1024] = {0};
        int number_count = 0;
        int row_count = 1;
        while (n != NULL) {
            numbers[0][number_count++] = atoi(n);
            n = strtok(NULL, " ");
        }
        while (true) {
            bool complete = true;
            int length = number_count - row_count;
            for (int i = 0; i < length; ++i) {
                int number = numbers[row_count - 1][i + 1] - numbers[row_count - 1][i];
                numbers[row_count][i] = number;
                if (number != 0)
                    complete = false;
            }
            row_count++;
            if (complete)
                break;
        }

        int start_number = numbers[row_count - 1][0];
        for (int i = row_count - 2; i >= 0; --i) {
            int length = number_count - i;
            int start = numbers[i][0];
            start_number = start - start_number;
        }

        //printf("final: %d\n", final_number);
        sum += start_number;
    }

    printf("sum: %d\n", sum);
}
