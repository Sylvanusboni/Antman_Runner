/*
** EPITECH PROJECT, 2022
** get_nb_rows.c
** File description:
** to get the rows number
*/

int get_nb_rows(char *str)
{
    int y = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            y++;
        }
    }
    return (y);
}
