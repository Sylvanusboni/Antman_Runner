/*
** EPITECH PROJECT, 2023
** build
** File description:
** map
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "struct.h"

void get_nb_rows(all_t *game)
{
    int y = 0;
    for (int i = 0; game->buffer[i] != '\0'; i++) {
        if (game->buffer[i] == '\n') {
            game->rows++;
        }
    }
}

void get_nb_cols(all_t *game)
{
    int k = 0, x = 0, n = 0;
    game->cols = (int *)malloc(sizeof(int) * (game->rows));
    for (k = 0; game->buffer[k] != '\0'; k++) {
        if (game->buffer[k] != '\n')
            x++;
        if (game->buffer[k] == '\n') {
            game->cols[n] = x + 1;
            n++;
            x = 0;
        }
    }
}

char **map_2D(all_t *game)
{
    int x = 0, j = 0;
    game->map = (char **)malloc(sizeof(char *) * (game->rows + 1));
    game->map[game->rows] = NULL;
    for (int i = 0; i < game->rows; i++) {
        game->map[i] = (char *)malloc(sizeof(char) * game->cols[i] + 1);
        for (j = 0; j < game->cols[i]; j++) {
            game->map[i][j] = game->buffer[x];
            printf("%c", game->buffer[x]);
            x++;
        } game->map[i][j] = '\0';
    }
    return (game->map);
}
