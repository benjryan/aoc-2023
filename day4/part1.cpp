#include <stdio.h>

int main()
{
    FILE* fp = fopen("input.txt", "r");
    char line[1024];
    int sum = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        int card_id;
        int winners[10];
        int mine[25];
        sscanf(line, "Card %d: %d %d %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 
               &card_id, 
               &winners[0],&winners[1],&winners[2],&winners[3],&winners[4],&winners[5],&winners[6],&winners[7],&winners[8],&winners[9],
               &mine[0],&mine[1],&mine[2],&mine[3],&mine[4],&mine[5],&mine[6],&mine[7],&mine[8],&mine[9],
               &mine[10],&mine[11],&mine[12],&mine[13],&mine[14],&mine[15],&mine[16],&mine[17],&mine[18],&mine[19],
               &mine[20],&mine[21],&mine[22],&mine[23],&mine[24]);
        //printf("Card %d: ", card_id);
        //for (int i = 0; i < 10; ++i)
        //    printf("%d ", winners[i]);
        //printf("| ");
        //for (int i = 0; i < 25; ++i)
        //    printf("%d ", mine[i]);
        //printf("\n");

        int score = 0;
        for (int i = 0; i < 25; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (mine[i] == winners[j]) {
                    score = (score == 0) ? 1 : score * 2;
                    break;
                }
            }
        }
        sum += score;
    }

    printf("%d\n", sum);
}
