/*
** EPITECH PROJECT, 2022
** write_score
** File description:
** to write score
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "struct.h"
#include <stdlib.h>
#include <stdio.h>

int my_strlen ( char const * str );

int score_len(int nb)
{
    int j = 1;
    while (nb >= 10) {
        j++;
        nb /= 10;
    } return j;
}

char *reverse_string(char *str)
{
    char *rev_str = (char *)malloc(sizeof(char) * (my_strlen(str) + 1));
    int i = my_strlen(str) - 1, j = 0;
    for (i = 0; i >= 0; i--, j++) {
        rev_str[j] = str[i];
    } rev_str[j] = '\0';
    return rev_str;
}

char *get_score(All_t *game)
{
    int length = score_len(game->score);
    int score = game->score;
    game->string = (char *)malloc(sizeof(char) * (length + 1));
    game->string[length] = '\0';
    int len = length - 1;
    while (len >= 0) {
        game->string[len] = (score % 10) + 48;
        score /= 10;
        len--;
    }
    return game->string;
}

char *get_time(All_t *game)
{
    int length = score_len(game->seconds3);
    int time = game->seconds3;
    game->string2 = (char *)malloc(sizeof(char) * (length + 1));
    game->string2[length] = '\0';
    int len = length - 1;
    while (len >= 0) {
        game->string2[len] = (time % 10) + 48;
        time /= 10;
        len--;
    }
    return game->string2;
}

void init_score(All_t *game)
{
    game->font = sfFont_createFromFile("ac.ttf");
    game->text = sfText_create();
    game->text2 = sfText_create();
    game->text4 = sfText_create();
    
    sfText_setFont(game->text, game->font);
    sfText_setFont(game->text2, game->font);
    sfText_setFont(game->text4, game->font);

    game->text5 = sfText_create();
    sfText_setFont(game->text5, game->font);
}

void write_score(All_t *game)
{
    sfText_setString(game->text, "Score : ");
    sfText_setString(game->text2, get_score(game));
    sfText_setString(game->text4, get_time(game));
    sfText_setString(game->text5, "Your Score : ");
    
    sfText_setCharacterSize(game->text, 100);
    sfText_setCharacterSize(game->text2, 100);
    sfText_setCharacterSize(game->text4, 100);
    sfText_setCharacterSize(game->text5, 100);
    
    sfText_setPosition(game->text2, (sfVector2f){0, 0});
    sfText_setPosition(game->text, (sfVector2f){0, 850});
    /* if ((40 - game->seconds2) <= 5) */
    /*     sfText_setColor(game->text4, sfRed); */
    sfText_setPosition(game->text4, (sfVector2f){1700, 0});
    sfText_setPosition(game->text5, (sfVector2f){450, 50});
}
