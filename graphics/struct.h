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

    typedef struct all {
        int ghost;
        int nb;
        int **tab;
        sfView *view;
        sfVideoMode mode;
        sfRenderWindow* window;
        sfEvent event;
        sfClock *clock;
        sfTime time;
        double seconds;
        double seconds2; 
        sfFont *font;
        sfText *text;
        sfText *text2;
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
        char **map;
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
#endif
