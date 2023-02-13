/*
** EPITECH PROJECT, 2023
** open
** File description:
** window
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <unistd.h>
#include "struct.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void get_nb_rows(all_t *game);
void get_nb_cols(all_t *game);
char **map_2D(all_t *game);

void init_background(all_t *game)
{
    game->texture = sfTexture_createFromFile("x1080.jpg",
    NULL);
    game->sprite = sfSprite_create();
    sfSprite_setTexture(game->sprite, game->texture, sfTrue);

    game->texture_X = sfTexture_createFromFile("1779754.png",
    NULL);
    game->sprite_X = sfSprite_create();
    sfSprite_setScale(game->sprite_X, (sfVector2f){0.5, 0.5});
    sfSprite_setPosition(game->sprite_X, (sfVector2f){1900, 0});
    sfSprite_setTexture(game->sprite_X, game->texture_X, sfTrue);

    game->texture_O = sfTexture_createFromFile("index.png",
    NULL);
    game->sprite_O = sfSprite_create();
    sfSprite_setPosition(game->sprite_O, (sfVector2f){2200, 0});
    sfSprite_setTexture(game->sprite_O, game->texture_O, sfTrue);

    game->joueur_t = sfTexture_createFromFile("player.png",
    NULL);
    game->joueur = sfSprite_create();
    sfSprite_setPosition(game->joueur, (sfVector2f){10, 831});
    sfSprite_setScale(game->joueur, (sfVector2f){0.46, 0.37});
    sfSprite_setTexture(game->joueur, game->joueur_t, sfTrue);
    
    game->texture_M = sfTexture_createFromFile("Wall_Brown.png",
    NULL);
    game->sprite_M = sfSprite_create();
    //sfSprite_setScale(game->sprite_M, (sfVector2f){0.5, 0.5});
    sfSprite_setTexture(game->sprite_M, game->texture_M, sfTrue);
}

Mur_t *init_mur(void)
{
    Mur_t *mur = malloc(sizeof(*mur));
    mur_t *new = (mur_t *)malloc(sizeof(*new));
    new->texture_M = sfTexture_createFromFile("Wall_Brown.png",
    NULL);
    new->sprite_M = sfSprite_create();
    sfSprite_setTexture(new->sprite_M, new->texture_M, sfTrue);
    new->next = NULL;
    mur->first = new;
    return mur;
}

Ghost_t *init_ghost(void)
{
    Ghost_t *ghost = (Ghost_t *)malloc(sizeof(*ghost));
    ghost_t *new = (ghost_t *)malloc(sizeof(*new));
    new->ghost_t = sfTexture_createFromFile("Ghost.png",
    NULL);
    new->ghost = sfSprite_create(); new->x = new->y = 0;
    sfSprite_setTexture(new->ghost, new->ghost_t, sfTrue);
    new->next = NULL;
    ghost->first = new;
    return ghost;
}

Ghost_t *add_ghost(Ghost_t *ghost, int x, int y)
{
    ghost_t *new = (ghost_t *)malloc(sizeof(*new));
    new->ghost_t = sfTexture_createFromFile("Ghost.png",
    NULL);
    new->ghost = sfSprite_create();
    sfSprite_setTexture(new->ghost, new->ghost_t, sfTrue);
    sfSprite_setPosition(new->ghost, (sfVector2f){x, y});
    new->next =	ghost->first; new->x = x, new->y = y;
    ghost->first = new;
    return ghost;
}

Mur_t *add_mur(Mur_t *mur, int x, int y)
{
    mur_t *new = (mur_t *)malloc(sizeof(*new));
    new->texture_M = sfTexture_createFromFile("Wall_Brown.png",
    NULL);
    new->sprite_M = sfSprite_create();
    sfSprite_setTexture(new->sprite_M, new->texture_M, sfTrue);
    sfSprite_setPosition(new->sprite_M, (sfVector2f){x, y});
    new->next = mur->first;
    mur->first = new;
    return mur;
}

int count_box(all_t *game)
{
    int i = 0; game->box = 0;
    while (game->buffer[i]) {
        if (game->buffer[i] == 'M')
            game->box++;
        i++;
    }
    return game->box;
}

void place_wall_b(all_t *game, Mur_t *mur, Ghost_t *ghost)
{
    int i = 0, x = 0, y = 0, k = -1;
    int n = 0;
    while (game->buffer[i]) {
        if (game->buffer[i] == '\n') {
            y += 64; x = 0;
        } if (game->buffer[i] == 'M') {
            add_mur(mur, x, y);
            x += 64; n++;
        } if (game->buffer[i] == 'G') {
            add_ghost(ghost, x, y);
            x += 64;
        }
        (game->buffer[i] == ' ') ? x += 64 : 0;
        i++;
    }
}

void animation(Mur_t *mur, all_t *game)
{
    mur_t *tmp = mur->first->next; int n = 0;
    while (tmp) {
        sfSprite_move(tmp->sprite_M, (sfVector2f){-0.3, 0});
        sfRenderWindow_drawSprite(game->window, tmp->sprite_M, NULL);
        tmp = tmp->next;
    } game->n -= 0.3;
}

void anim_ghost(Ghost_t *ghost, all_t *game)
{
    ghost_t *tmp = ghost->first->next;
    sfVector2f pos = {0, 0};
    while (tmp) {
        pos = sfSprite_getPosition(tmp->ghost);
        if (pos.x < tmp->x - 10)
            sfSprite_move(tmp->ghost, (sfVector2f){0.8, 0});
        else
            sfSprite_move(tmp->ghost, (sfVector2f){-0.8, 0});
        sfRenderWindow_drawSprite(game->window, tmp->ghost, NULL);
        tmp = tmp->next;
    }
}

void init_rect(all_t *game)
{
    game->rect.top = 0;
    game->rect.left = 0;
    game->rect.width = 139;
    game->rect.height = 171;
    sfSprite_setTextureRect(game->joueur, game->rect);
}

void move_player(all_t *game)
{
    game->time = sfClock_getElapsedTime(game->clock);
    game->seconds = game->time.microseconds / 100000.0;
    if (game->seconds >= 1.0) {
        game->rect.left += 139;
        if (game->rect.left >= 834)
            game->rect.left = 0;
        sfSprite_setTextureRect(game->joueur, game->rect);
        sfClock_restart(game->clock);
    }
}

void move_up(all_t *game)
{
    game->time = sfClock_getElapsedTime(game->clock);
    game->seconds = game->time.microseconds / 100000.0;
    game->rect.left = 834;
    if (game->seconds >= 1.0 && game->value == 3) {
        game->rect.left += 139;
        if (game->rect.left >= 1110)
            game->rect.left = 834;
        sfSprite_setTextureRect(game->joueur, game->rect);
        sfClock_restart(game->clock);
    }
}

void move_sprite(all_t *game)
{
    sfSprite_move(game->sprite_X, (sfVector2f){-0.05, 0});
    game->pos_X = sfSprite_getPosition(game->sprite_X);
    if (game->pos_X.x <= 875)
        sfSprite_setPosition(game->sprite_X, (sfVector2f){1900, 0});

    sfSprite_move(game->sprite_O, (sfVector2f){-0.02, 0});
    game->pos_O = sfSprite_getPosition(game->sprite_O);
    if (game->pos_O.x <= 875)
	sfSprite_setPosition(game->sprite_O, (sfVector2f){2200, 0});
}

void analyse_event(all_t *game)
{
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        if (game->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window);
        }
    }
}

void open_map(all_t *game, char *filepath)
{
    struct stat star;
    stat(filepath, &star);
    int size = star.st_size;
    int fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return;
    game->buffer = malloc(sizeof(char) * size + 1);
    game->buffer[size] = '\0';
    int rd = read(fd, game->buffer, size);
    if (rd == -1)
        return;
    close(fd);
}

void place_wall(all_t *game)
{
    int i = 0, x = 0, y = 0;
    while (game->buffer[i]) {
        if (game->buffer[i] == '\n') {
            y += 64; x = 0;
        } if (game->buffer[i] == 'M') {
            sfSprite_setPosition(game->sprite_M, (sfVector2f){x, y});
            sfSprite_move(game->sprite_M, (sfVector2f){-10, 0});
            sfRenderWindow_drawSprite(game->window, game->sprite_M, NULL);
            x += 64;
        }
        i++;
    }
}

void check_collisions(all_t *game, Mur_t *mur)
{
    mur_t *tmp = mur->first->next;
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    sfVector2f position = {0, 0};
    game->position = sfSprite_getPosition(game->joueur);
}

void collision(all_t *game)
{
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    int y = roundf((t) / 64), x = roundf((l - game->n) / 64);

    if (game->map[y - 1][x] == 'M');
}

void check_space(all_t *game)
{
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    int y = roundf(t / 64), x = roundf((l - game->n) / 64);

    if (game->map[y + 1][x] == ' ' && game->event.type != sfEvtKeyPressed) {
        game->jumping = true;
        game->velocity = 0;
    }
}

void manage_jump(all_t *game, Mur_t *mur)
{
    game->position = sfSprite_getPosition(game->joueur);
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    int y = roundf(t / 64), x = roundf((l - game->n) / 64);
    if (game->jumping) {
        game->position.y -= game->velocity;
        game->velocity -= game->gravity;
        game->jump_height--;
        if (game->position.x <= 1800)
            game->position.x += 2.5;
        game->rect.left = 838;
        sfSprite_setTextureRect(game->joueur, game->rect);
        if (game->map[y - 1][x] == 'M')
            game->velocity = game->jump_height;
        if (game->velocity < 0 && game->map[y + 1][x] == 'M' && game->map[y - 1][x] == ' ') {
            game->jumping = false;
            game->velocity = game->jump;
            game->jump_height = 0; game->collision = false;
            game->rect.left = 977;
            game->position.y = y * 64;
            sfSprite_setTextureRect(game->joueur, game->rect);
        }
    } else {
        if (game->map[y + 1][x] == ' ') {
            game->position.y += 12;
            game->position.x += 1;
        } else if (game->map[y + 1][x] == 'M')
            game->position.y = y * 64;
    }
    sfSprite_setPosition(game->joueur, game->position);
}

void move_right(all_t *game)
{
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    int y = roundf((t) / 64), x = roundf((l - game->n) / 64);
    
    game->position = sfSprite_getPosition(game->joueur);
    
    if (game->position.x <= 1800 && game->map[y][x + 1] == ' ') {
        game->position.x += 4;
    }
    sfSprite_setPosition(game->joueur, game->position);
}

void open_window(all_t *game, char **av, Mur_t *mur, Ghost_t *ghost)
{
    game->clock = sfClock_create();
    game->mode.height = 1080;
    game->mode.width = 1920;
    game->mode.bitsPerPixel = 32;
    game->window = sfRenderWindow_create(game->mode, "My hunter",
                                         sfResize | sfClose, NULL);
    game->gravity = 1; game->jump = 20; game->a = 0.04; game->nb = 0;
    game->jumping = false; game->velocity = game->jump; game->jump_height = 0;
    init_background(game); init_rect(game); open_map(game, av[1]); count_box(game);
    get_nb_rows(game); get_nb_cols(game); int i = 0; map_2D(game); game->n = 0;
    place_wall_b(game, mur, ghost); game->value = 0; game->collision = false;
    game->scale = false; sfSprite_setColor(game->joueur, sfRed);
    while (sfRenderWindow_isOpen(game->window)) {
        
        analyse_event(game);
        sfRenderWindow_clear(game->window, sfWhite);
        sfRenderWindow_drawSprite(game->window, game->sprite, NULL);
        sfRenderWindow_drawSprite(game->window, game->sprite_O, NULL);
        sfRenderWindow_drawSprite(game->window, game->sprite_X, NULL);
        sfRenderWindow_drawSprite(game->window, game->joueur, NULL);

        game->rect_f = sfSprite_getGlobalBounds(game->joueur);
        float l = game->rect_f.left, t = game->rect_f.top;
        float w = game->rect_f.width, h = game->rect_f.height;
        int y = roundf((t) / 64), x = roundf((l - game->n) / 64);
        if (game->event.type == sfEvtKeyPressed && game->event.key.code == sfKeyUp && game->map[y + 1][x] == 'M' && game->map[y - 1][x] == ' ') {
            game->jumping = true; game->value = 3;
            game->scale = false;
            sfSprite_setScale(game->joueur, (sfVector2f){0.46, 0.37});
        } if (game->event.type == sfEvtKeyPressed && game->event.key.code == sfKeyRight && game->map[y][x + 1] == ' ') {
            move_right(game); game->value = 1;
            game->scale = false;
            sfSprite_setScale(game->joueur, (sfVector2f){0.46, 0.37});
        } if (game->event.type == sfEvtKeyPressed && game->event.key.code == sfKeyDown) {
            sfSprite_setScale(game->joueur, (sfVector2f){0.25, 0.25});
            game->scale = true;
        } if (game->map[y][x + 1] == 'M') {
            game->position = sfSprite_getPosition(game->joueur);
            game->position.x -= 0.3;
            sfSprite_setPosition(game->joueur, game->position);
        }
        manage_jump(game, mur);
        move_sprite(game); move_player(game); animation(mur, game);
        anim_ghost(ghost, game);
        sfRenderWindow_display(game->window);
        usleep(8000);
    } sfRenderWindow_destroy(game->window); mur_t *tmp = mur->first; mur_t *tmp2 = NULL;
    ghost_t *tmp3 = NULL;
    sfSprite_destroy(game->sprite); sfSprite_destroy(game->joueur);
    sfSprite_destroy(game->sprite_O); sfSprite_destroy(game->sprite_M);
    while (tmp) {
        sfSprite_destroy(tmp->sprite_M);
        tmp = tmp->next;
    } while (mur->first) {
        tmp2 = mur->first->next;
        free(mur->first);
        mur->first = tmp2;
    } while (ghost->first) {
        tmp3 = ghost->first->next;
        free(ghost->first);
        ghost->first = tmp3;
    }
    int n = 0;
    free(game->cols);
    while (n < game->rows) {
        free(game->map[n]);
        n++;
    } free(game->map);
    free(game->buffer);
    sfSprite_destroy(game->sprite_X);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        write(1, "missed arguments\n", 17);
        return 84;
    }
    all_t *game = malloc(sizeof(*game));
    Mur_t *mur = init_mur();
    Ghost_t *ghost = init_ghost();
    open_window(game, av, mur, ghost);
    free(game); free(mur); free(ghost);
    return 0;
}
