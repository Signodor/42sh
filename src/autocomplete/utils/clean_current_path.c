/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** clean_current_path
*/

#include "auto_complete_sys.h"

void mv_left_arr(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = str[i + 1];
}

char *clean_beg(char *res)
{
    int i = 0;

    for (i = strlen(res); res[i] != '/' && i > 0; i--);
    if (res[i] == 0) {
        free(res);
        return (NULL);
    }
    for (int j = i; j > 0; j--)
        mv_left_arr(res);
    if (res[0] == '/')
        mv_left_arr(res);
    return (res);
}

char *clean_current_path(char *current_path)
{
    char *res = NULL;

    if (!current_path)
        return (NULL);
    res = my_strdup(current_path);
    if (!res)
        return (NULL);
    res = clean_beg(res);
    return (res);
}