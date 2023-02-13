/*
** EPITECH PROJECT, 2022
** get_nb_cols
** File description:
** to get the columns number
*/

#include <stdlib.h>

int get_nb_rows(char *str);

int *get_nb_cols(char *str, int nb_rows)
{
    int k = 0, x = 0, n = 0;
    int *tab = (int *)malloc(sizeof(int) * (nb_rows + 1));
    tab[nb_rows] = 0;
    for (k = 0; str[k] != '\0'; k++) {
        if (str[k] != '\n')
            x++;
        if (str[k] == '\n') {
            if ((x) > tab[nb_rows])
                tab[nb_rows] = (x);
            tab[n] = x + 1;
            n++;
            x = 0;
        }
    } return tab;
}
