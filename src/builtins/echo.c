/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser
*/

#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "echo.h"

const struct echo mnemos[] = {
    {'\\', '\\'},
    {'a', '\a'},
    {'b', '\b'},
    {'e', '\e'},
    {'f', '\f'},
    {'n', '\n'},
    {'r', '\r'},
    {'t', '\t'},
    {'v', '\v'},
    {'\"', '\"'},
    {0, 0},
};

int disp_char(char **w, char c)
{
    if (c != '\\')
        return (printf("%c", c));
    c = *(*w)++;
    if (!c)
        return (printf("\\"));
    if (c == 'c')
        return (0);
    for (size_t i = 0; mnemos[i].letter; i++)
        if (mnemos[i].letter == c)
            return (printf("%c", mnemos[i].res));
    return (printf("\\%c", c));
}

int c_echo(char **argv, vector_t *env)
{
    char c;
    char *w;
    char stop = 1;

    for (size_t i = 1; argv[i] && stop; i++) {
        w = argv[i];
        while ((c = *w++) && stop)
            stop = disp_char(&w, c);
        if (argv[i + 1])
            printf(" ");
    }
    printf("\n");
    return (0);
}