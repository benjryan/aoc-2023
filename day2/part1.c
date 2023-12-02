#include <stdio.h>
#include <string.h>

int main()
{
    FILE* file = fopen("input.txt", "r");
    char line[1024];
    int sum = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int game_id;
        sscanf(line, "Game %d", &game_id);
        strtok(line, ":");
        char* games = strtok(NULL, ":");
        if (games == NULL)
            continue;

        char* next_game;
        char* game = strtok_r(games, ";", &next_game);
        while (game != NULL)
        {
            char* next_action;
            char* action = strtok_r(game, ",", &next_action);
            while (action != NULL)
            {
                int count;
                char color[16];
                sscanf(action, "%d %s", &count, color);
                if (strcmp(color, "red") == 0)
                {
                    if (count > 12)
                        goto nextline;
                }
                else if (strcmp(color, "green") == 0)
                {
                    if (count > 13)
                        goto nextline;
                }
                else
                {
                    if (count > 14)
                        goto nextline;
                }

                //printf("%d %s, ", count, color);
                action = strtok_r(next_action, ",", &next_action);
            }

            game = strtok_r(next_game, ";", &next_game);
        }

        sum += game_id;

nextline:
    }

    printf("%d", sum);
}
