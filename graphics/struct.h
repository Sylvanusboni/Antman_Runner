/*
** EPITECH PROJECT, 2022
** struct.h
** File description:
** struct.h
*/

#ifndef STRUCT_H
    #define STRUCT_H

    #include <SFML/Graphics.h>
    #include <stdio.h>
    #include <math.h>
    #include <SFML/Audio.h>
    #define all_t All_t

    typedef struct all {
        int score;
        int ghost;
        char *string;
        char *string2;
        char *string3;
        int fd;
        int nb;
        int nbr;
        int size;
        char *str;
        int **tab;
        sfView *view;
        sfVideoMode mode;
        sfRenderWindow* window;
        sfEvent event;
        sfClock *clock;
        sfTime time;
        double seconds;
        sfClock *clock2;
        sfClock *clock3;
        double seconds2;
        double seconds3;
        sfTime time2;
        sfTime time3;
        sfFont *font;
        sfText *text;
        sfText *text2;
        sfText *text3;
        sfText *text4;
        sfText *text5;
        sfText *text6;
        sfText *text7;
        sfTexture *texture;
        sfTexture *texture_X;
        sfTexture *joueur_t;
        sfSprite *sprite;
        sfSprite *sprite_X;
        sfSprite *joueur;
        sfTexture *texture_O;
        sfSprite *sprite_O;
        sfTexture *texture_M;
        sfSprite *sprite_M;
        sfTexture *bg_t;
        sfSprite *bg;
        sfTexture *end_t;
        sfSprite *end;
        sfVector2f end_pos;
        sfIntRect rect;
        sfIntRect rect2;
        sfFloatRect rect_f;
        sfFloatRect rect_f2;
        sfVector2f pos_M;
        sfVector2f pos_X;
        sfVector2f pos_O;
        sfVector2f mouse_position;
        sfVector2f position;
        sfVector2f posRel;
        sfVector2f posAbs;
        sfVector2f bg_pos;
        sfVector2f sp_pos;
        sfVector2f tmp_pos;
        char **map;
        sfMusic *music;
        sfMusic *music2;
        int gravity;
        int jump;
        double a;
        sfBool jumping;
        int velocity;
        char *buffer;
        int value;
        sfBool collision;
        sfBool scale;
        int *cols;
        int rows;
        int box;
        double n;
        int jump_height;
    } all_t;

    typedef struct mur
    {
        sfTexture *texture_M;
        sfSprite *sprite_M;
        struct mur *next;
    } mur_t;

    typedef struct f_mur {
        mur_t *first;
    } Mur_t;

    typedef struct ghost
    {
        sfTexture *ghost_t;
	sfSprite *ghost;
        int x;
        int y;
        struct ghost *next;
    } ghost_t;

    typedef struct Ghost {
        ghost_t *first;
    } Ghost_t;

    typedef struct squel {
        sfTexture *sq_t;
        sfSprite *sq;
        sfIntRect sq_rect;
        sfBool coins;
        struct squel *next;
    } squel_t;

    typedef struct Squel {
        squel_t *first;
    } Squel_t;
#endif
