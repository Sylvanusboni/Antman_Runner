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
#include <SFML/Audio.h>

void get_nb_rows(all_t *game);
void get_nb_cols(all_t *game);
char **map_2D(all_t *game);
void init_score(All_t *game);
void write_score(All_t *game);
void play_music(All_t *game);

void init_background(all_t *game)
{
    game->texture = sfTexture_createFromFile("snow_bg.jpg",
    NULL);
    game->sprite = sfSprite_create();
    sfSprite_setTexture(game->sprite, game->texture, sfTrue);

    game->bg_t = sfTexture_createFromFile("snow_bg.jpg", NULL);
    game->bg = sfSprite_create();
    sfSprite_setPosition(game->bg, (sfVector2f){1920, 0});
    sfSprite_setTexture(game->bg, game->bg_t, sfTrue);

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
    sfSprite_setPosition(game->joueur, (sfVector2f){10, 100});
    sfSprite_setScale(game->joueur, (sfVector2f){0.46, 0.37});
    sfSprite_setTexture(game->joueur, game->joueur_t, sfTrue);
    
    game->texture_M = sfTexture_createFromFile("Wall_Brown.png",
    NULL);
    game->sprite_M = sfSprite_create();
    sfSprite_setTexture(game->sprite_M, game->texture_M, sfTrue);
}

Mur_t *init_mur(void)
{
    Mur_t *mur = malloc(sizeof(*mur));
    mur_t *new = (mur_t *)malloc(sizeof(*new));
    new->texture_M = sfTexture_createFromFile("snow_wall.png",
    NULL);
    new->sprite_M = sfSprite_create();
    sfSprite_setScale(new->sprite_M, (sfVector2f){0.89, 0.94});
    sfSprite_setTexture(new->sprite_M, new->texture_M, sfTrue);
    new->next = NULL;
    mur->first = new;
    return mur;
}

Ghost_t *init_ghost(void)
{
    Ghost_t *ghost = (Ghost_t *)malloc(sizeof(*ghost));
    ghost_t *new = (ghost_t *)malloc(sizeof(*new));
    new->ghost_t = sfTexture_createFromFile("snowman.png",
    NULL);
    new->ghost = sfSprite_create(); new->x = new->y = 0;
    sfSprite_setScale(new->ghost, (sfVector2f){0.40, 0.2909});
    sfSprite_setTexture(new->ghost, new->ghost_t, sfTrue);
    new->next = NULL;
    ghost->first = new;
    return ghost;
}

Ghost_t *add_ghost(Ghost_t *ghost, int x, int y)
{
    ghost_t *new = (ghost_t *)malloc(sizeof(*new));
    new->ghost_t = sfTexture_createFromFile("snowman.png", NULL);
    new->ghost = sfSprite_create();
    sfSprite_setTexture(new->ghost, new->ghost_t, sfTrue);
    sfSprite_setPosition(new->ghost, (sfVector2f){x, y});
    sfSprite_setScale(new->ghost, (sfVector2f){0.40, 0.2909});
    new->next = ghost->first; new->x = x, new->y = y;
    ghost->first = new;
    return ghost;
}

Squel_t *init_sq(void)
{
    Squel_t *sql = (Squel_t *)malloc(sizeof(*sql));
    squel_t *new = (squel_t *)malloc(sizeof(*new));
    new->sq_t = sfTexture_createFromFile("coins.png",
    NULL);
    new->sq = sfSprite_create();
    sfSprite_setTexture(new->sq, new->sq_t, sfTrue);
    new->next = NULL;
    sql->first = new;
    return sql;
}

void init_sq_rect(squel_t *elem);

Squel_t *add_sql(Squel_t *sql, int x, int y)
{
    squel_t *new = (squel_t *)malloc(sizeof(*new));
    new->sq_t =	sfTexture_createFromFile("coins.png", NULL);
    new->sq = sfSprite_create();
    sfSprite_setPosition(new->sq, (sfVector2f){x + 15, y + 15});
    sfSprite_setScale(new->sq, (sfVector2f){0.45, 0.45});
    sfSprite_setTexture(new->sq, new->sq_t, sfTrue);
    init_sq_rect(new); new->coins = false;
    new->next =	sql->first;
    sql->first = new;
    return sql;
}

void init_sq_rect(squel_t *elem)
{
    elem->sq_rect.top = 0;
    elem->sq_rect.left = 0;
    elem->sq_rect.width = 97;
    elem->sq_rect.height = 98;
    sfSprite_setTextureRect(elem->sq, elem->sq_rect);
}

void move_sq_rect(squel_t *sql, all_t *game)
{
    game->seconds2 = game->time2.microseconds / 100000.0;
    if (game->seconds2 >= 1.0) {
        sql->sq_rect.left += 97;
        if (sql->sq_rect.left >= 486)
            sql->sq_rect.left = 0;
        sfSprite_setTextureRect(sql->sq, sql->sq_rect);
        sfClock_restart(game->clock2);
    }
}

void sq_animation(Squel_t *sql, all_t *game)
{
    squel_t *tmp = sql->first;
    squel_t *tmp2 = NULL; int n = 0;
    game->time2 = sfClock_getElapsedTime(game->clock2);
    game->time3 = sfClock_getElapsedTime(game->clock3);
    game->seconds3 = game->time3.microseconds / 1000000.0;
    int time = 0;
    while (tmp->next) {
        move_sq_rect(tmp, game);
        sfSprite_move(tmp->sq, (sfVector2f){-0.8, 0});
        sfFloatRect sq_rect = sfSprite_getGlobalBounds(tmp->sq);
        float l = sq_rect.left, t = sq_rect.top;
        float w = sq_rect.width, h = sq_rect.height;
        
        game->rect_f = sfSprite_getGlobalBounds(game->joueur);
//        game->position = sfSprite_getPosition(game->joueur);
        float lj = game->rect_f.left, tj = game->rect_f.top;
        float wj = game->rect_f.width, hj = game->rect_f.height;
        int y = roundf((tj) / 64), x = roundf((lj - game->n) / 64);
        
/*         sfVector2f pos = sfSprite_getPosition(tmp->sq); */
/*         game->position = sfSprite_getPosition(game->joueur); */
        if (l > lj && l < lj + wj && t > tj && t < tj + h) {
            game->map[y][x + 1] = ' ';
            tmp->coins = true;
            sfMusic_play(game->music);
            game->score++;
        } if (!tmp->coins)
              sfRenderWindow_drawSprite(game->window, tmp->sq, NULL);
        tmp = tmp->next;
    }
}

Mur_t *add_mur(Mur_t *mur, int x, int y)
{
    mur_t *new = (mur_t *)malloc(sizeof(*new));
    new->texture_M = sfTexture_createFromFile("snow_wall.png",
    NULL);
    new->sprite_M = sfSprite_create();
    sfSprite_setScale(new->sprite_M, (sfVector2f){0.89, 0.94});
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


void place_wall_b(all_t *game, Mur_t *mur, Ghost_t *ghost, Squel_t *sql)
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
        } if (game->buffer[i] == 'S') {
            add_sql(sql, x, y);
            x += 64;
        } if (game->buffer[i] == 'E')
              x += 64;
        (game->buffer[i] == ' ') ? x += 64 : 0;
        i++;
    }
}

void animation(Mur_t *mur, all_t *game)
{
    mur_t *tmp = mur->first; int n = 0;
    while (tmp->next) {
        sfSprite_move(tmp->sprite_M, (sfVector2f){-0.8, 0});
        sfRenderWindow_drawSprite(game->window, tmp->sprite_M, NULL);
        tmp = tmp->next;
    } game->n -= 0.8;
}

void anim_ghost(Ghost_t *ghost, all_t *game)
{
    ghost_t *tmp = ghost->first;
    sfVector2f pos = {0, 0};
    while (tmp->next) {
        pos = sfSprite_getPosition(tmp->ghost);
        /* if (pos.x < tmp->x - 10) */
        /*     sfSprite_move(tmp->ghost, (sfVector2f){0.8, 0}); */
        /* else */
        sfSprite_move(tmp->ghost, (sfVector2f){-0.8, 0});
        /* if (pos.y <= 10) { */
        /*     pos.y = 900; */
        /*     sfSprite_setPosition(tmp->ghost, pos); */
        /* } */
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
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    int y = roundf(t / 64), x = roundf((l - game->n) / 64);
    if (game->jumping) {
        game->position.y -= game->velocity;
        game->velocity -= game->gravity;
        game->jump_height--;
        if (game->position.x <= 1800 || game->event.type == sfEvtKeyPressed && game->event.key.code == sfKeyRight) {
            if (game->map[y][x + 1] != 'M' && game->velocity != 15)
                game->position.x += 2.5;
        }
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
        if (game->map[y + 1][x] != 'M') {
            game->position.y += 12;
            game->position.x += 1;
        } else if (game->map[y + 1][x] == 'M')
            game->position.y = y * 64;
    }
}

void move_right(all_t *game)
{
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    int y = roundf((t) / 64), x = roundf((l - game->n) / 64);
    
//    game->position = sfSprite_getPosition(game->joueur);
    
    if (game->position.x <= 1800 && game->map[y][x + 1] == ' ') {
        game->position.x += 4;
    }
//    sfSprite_setPosition(game->joueur, game->position);
}

void move_background(all_t *game)
{
    double x = 0;
    game->tmp_pos = sfSprite_getPosition(game->sprite);
    sfSprite_move(game->sprite, (sfVector2f){-10, 0});
    
    sfSprite_move(game->bg, (sfVector2f){-10, 0});

    if (game->bg_pos.x <= game->tmp_pos.x - 1920) {
        game->tmp_pos.x = 0;
        sfSprite_setPosition(game->bg, game->tmp_pos);
        game->tmp_pos.x = 1920;
        sfSprite_setPosition(game->sprite, game->tmp_pos);        
    }
}

void win(all_t *game)
{
    game->rect_f = sfSprite_getGlobalBounds(game->joueur);
    float l = game->rect_f.left, t = game->rect_f.top;
    float w = game->rect_f.width, h = game->rect_f.height;
    int y = roundf((t) / 64), x = roundf((l - game->n) / 64);
    if (l > game->end_pos.x) {
        sfRenderWindow_drawSprite(game->window, game->end, NULL);
    }
}

void open_window(all_t *game, char **av, Mur_t *mur, Ghost_t *ghost, Squel_t *sql)
{
    game->clock = sfClock_create();
    game->clock2 = sfClock_create();
    game->clock3 = sfClock_create();
    game->mode.height = 1080;
    game->mode.width = 1920;
    game->mode.bitsPerPixel = 32;
    game->window = sfRenderWindow_create(game->mode, "My hunter",
                                         sfResize | sfClose, NULL);
    game->gravity = 1; game->jump = 15; game->a = 0.04; game->nb = 0;
    game->jumping = false; game->velocity = game->jump; game->jump_height = 0;
    init_background(game); init_rect(game); open_map(game, av[1]); count_box(game);
    get_nb_rows(game); get_nb_cols(game); int i = 0; map_2D(game); game->n = 0;
    place_wall_b(game, mur, ghost, sql); game->value = 0; game->collision = false;
    game->scale = false; //sfSprite_setColor(game->joueur, sfRed);
    game->bg_pos = sfSprite_getPosition(game->bg);
    /* game->end_pos = sfSprite_getPosition(game->end); */
    play_music(game);
    game-> score = 0; game->seconds3 = 0;
    init_score(game);
    while (sfRenderWindow_isOpen(game->window)) {
        
        analyse_event(game);
        sfRenderWindow_clear(game->window, sfWhite);
        sfRenderWindow_drawSprite(game->window, game->sprite, NULL);
        sfRenderWindow_drawSprite(game->window, game->sprite_O, NULL);
        sfRenderWindow_drawSprite(game->window, game->sprite_X, NULL);
        sfRenderWindow_drawSprite(game->window, game->joueur, NULL);
        sfRenderWindow_drawSprite(game->window, game->bg, NULL);

        game->rect_f = sfSprite_getGlobalBounds(game->joueur);
        game->position = sfSprite_getPosition(game->joueur);
        float l = game->rect_f.left, t = game->rect_f.top;
        float w = game->rect_f.width, h = game->rect_f.height;
        int y = roundf((t) / 64), x = roundf((l - game->n) / 64);
        if (game->map[y][x] == 'S')
            game->map[y][x + 1] = ' ';
        if (game->event.type == sfEvtKeyPressed && game->event.key.code == sfKeyUp && game->map[y + 1][x] == 'M' && game->map[y - 1][x] != 'M') {
            game->jumping = true; game->value = 3;
            if (game->scale) {
                game->scale = false;
                sfSprite_setScale(game->joueur, (sfVector2f){0.46, 0.37});
                game->position.y -= 30;
            }
        } if (game->event.type == sfEvtKeyPressed && game->event.key.code == sfKeyRight && game->map[y][x + 1] == ' ') {
            move_right(game); game->value = 1;
            if (game->scale) {
                game->scale = false;
                sfSprite_setScale(game->joueur, (sfVector2f){0.46, 0.37});
                game->position.y -= 30;
                sfSprite_setPosition(game->joueur, game->position);
            }
        } if (game->event.type == sfEvtKeyPressed && game->event.key.code == sfKeyDown) {
            sfSprite_setScale(game->joueur, (sfVector2f){0.10, 0.10});
            game->position.y += 5;
            game->scale = true;
        } if (game->map[y][x + 1] == 'M') {
            game->position = sfSprite_getPosition(game->joueur);
            game->position.x -= 0.8;
        } write_score(game);
        manage_jump(game, mur);
        move_sprite(game); move_player(game); animation(mur, game);
        anim_ghost(ghost, game); sq_animation(sql, game); //move_background(game);
        sfSprite_setPosition(game->joueur, game->position);
        sfRenderWindow_drawText(game->window, game->text, NULL);
        sfRenderWindow_drawText(game->window, game->text2, NULL);
        sfRenderWindow_drawText(game->window, game->text4, NULL);
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
    squel_t *tmp4 = NULL;
    while (sql->first) {
        tmp4 = sql->first->next;
        free(sql->first);
        sql->first = tmp4;
    }
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
    Squel_t *sql = init_sq();
    open_window(game, av, mur, ghost, sql);
    free(game); free(mur); free(ghost); free(sql);
    return 0;
}
