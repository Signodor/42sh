/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** my_str_replace
*/

#include <stdlib.h>
#include <string.h>
#include "str.h"

static void filler(char *str, char *to_replace, char *replacing, char *ret)
{
    int index = 0;

    for (int i = 0; str[i]; i++) {
        if (!strncmp(str + i, to_replace, strlen(to_replace))) {
            strncpy(ret + index, replacing, strlen(replacing));
            i += strlen(to_replace) - 1;
            index += strlen(replacing) - 1;
        } else
            ret[index] = str[i];
        index++;
    }
}

char *my_str_replace(char *str, char *to_replace, char *replacing)
{
    int count = 0;
    char *ret;

    if (!str)
        return (replacing);
    if (!to_replace)
        return (str);
    if (!replacing)
        replacing = my_strdup("");
    for (int i = 0; str[i]; i++)
        if (!strncmp(str + i, to_replace, strlen(to_replace)))
            count++;
    ret = calloc(sizeof(char), (strlen(str) - strlen(to_replace) *
    count + strlen(replacing) * count + 1));
    if (!ret)
        return (NULL);
    filler(str, to_replace, replacing, ret);
    return (ret);
}