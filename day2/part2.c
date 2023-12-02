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
        int max_red = 0, max_green = 0, max_blue = 0;
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
                    if (count > max_red)
                        max_red = count;
                }
                else if (strcmp(color, "green") == 0)
                {
                    if (count > max_green)
                        max_green = count;
                }
                else
                {
                    if (count > max_blue)
                        max_blue = count;
                }

                //printf("%d %s, ", count, color);
                action = strtok_r(next_action, ",", &next_action);
            }

            game = strtok_r(next_game, ";", &next_game);
        }

        int power = max_red * max_green * max_blue;
        sum += power;

nextline:
    }

    printf("%d", sum);
}
