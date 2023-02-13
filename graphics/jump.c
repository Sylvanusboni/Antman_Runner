/*
** EPITECH PROJECT, 2023
** jump
** File description:
** player
*/

void jump()
{
    sfVector2f posRel = {-50, 0};
    sfVector2f posAbs = {200, 300};

    posRel.y = -0.04 * (posRel.x * posRel.x) + 100;

    posAbs.x = posAbs.x + posRel.x + 50;
    posAbs.y = posAbs.y + posRel.y;
}
