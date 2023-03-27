/*
** EPITECH PROJECT, 2022
** play_music
** File description:
** play music
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "struct.h"

void play_music(All_t *game)
{
    game->music = sfMusic_createFromFile("collect_ring.ogg");
    game->music2 = sfMusic_createFromFile("run.ogg");
    sfMusic_play(game->music2);
}
