#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE  141
#define LINE_COUNT 140
#define FILE_SIZE LINE_SIZE * LINE_COUNT
#define IS_DIGIT(x) (x >= '0' && x <= '9')
#define IS_ALPHA(x) ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
#define IS_SYMBOL(x) (x >= 0x21 && x != '.' && !IS_DIGIT(x) && !IS_ALPHA(x))
#define ARRAY_COUNT(x) (sizeof(x)/sizeof(*x))

int offsets[] = { 
    -LINE_SIZE - 1, -LINE_SIZE, -LINE_SIZE + 1,
    -1, 1,
    LINE_SIZE - 1, LINE_SIZE, LINE_SIZE + 1
};

int main()
{
    char buffer[FILE_SIZE];
    FILE* fp = fopen("input.txt", "r");
    fread(buffer, 1, FILE_SIZE, fp);
    char number_str[8];
    int digit_count = 0;
    int found_symbol = 0;
    int sum = 0;
    
    for (int i = 0; i < FILE_SIZE; ++i) {
        char c = buffer[i];
        if (IS_DIGIT(c)) {
            number_str[digit_count++] = c;
            if (found_symbol)
                continue;

            for (int j = 0; j < ARRAY_COUNT(offsets); ++j) {
                int adj_idx = i + offsets[j];
                if (adj_idx < 0 || adj_idx >= FILE_SIZE)
                    continue;

                if (IS_SYMBOL(buffer[adj_idx])) {
                    found_symbol = 1;
                    break;
                }
            }
        } else {
            if (digit_count > 0 && found_symbol) {
                number_str[digit_count] = 0; // insert sentinel
                sum += atoi(number_str);
            }

            digit_count = 0;
            found_symbol = 0;
        }
    }

    printf("%d\n", sum);
}

