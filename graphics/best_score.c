#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include "struct.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int score_len(int nb);

int my_getnbr(All_t *game)
{
    struct stat star;
    stat("score", &star);
    game->size = star.st_size;
    game->nbr = 0;
    game->str = (char *)malloc(sizeof(char) * game->size + 1);
    game->str[game->size] = '\0';
    game->fd = open("score", O_RDWR);
    read(game->fd, game->str, game->size);
    for (int i = 0; game->str[i] != '\0'; i++) {
        if (game->str[i] >= 48 && game->str[i] <= 57) {
            game->nbr *= 10;
            game->nbr += game->str[i] - 48;
        }
    } close(game->fd);
    return game->nbr;
}

char *get_best(All_t *game)
{
    int length = score_len(game->nbr);
    int best_score = game->nbr;
    game->string3 = (char *)malloc(sizeof(char) * (length + 1));
    game->string3[length] = '\0';
    int len = length - 1;
    while (len >= 0) {
        game->string3[len] = (best_score % 10) + 48;
        best_score /= 10;
        len--;
    }
    return game->string3;
}

void write_best(All_t *game)
{
    sfText_setString(game->text6, "Best Score : ");
    sfText_setCharacterSize(game-> text6, 100);
    sfText_setPosition(game->text6, (sfVector2f){450, 500});
    
    sfText_setString(game->text7, get_best(game));
    sfText_setCharacterSize(game-> text7, 100);
    sfText_setPosition(game->text6, (sfVector2f){900, 500});
}

int best_score(All_t *game)
{
    if (game->score > game->nbr) {
        game->nbr = game->score;
        int lenght = score_len(game->nbr);
        game->fd = open("score", O_RDWR);
        write(game->fd, get_best(game), (lenght + 1));
        close(game->fd);
    }
    return game->nbr;
}
