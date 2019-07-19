/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** set_variable
*/

#include <stdio.h>
#include <string.h>
#include "str.h"
#include "env.h"
#include "utils.h"

static char *replacing(char *val, size_t pos)
{
    char *from = get_next_word(val + pos);
    char *to = get_variable_value(from);
    size_t len;
    char *res;

    if (!to || !from)
        return (val);
    len = strlen(to) - strlen(from) + strlen(val);
    res = my_malloc(sizeof(char) * len);
    strncpy(res, val, pos);
    strcpy(res + pos - 1, to);
    strcpy(res + pos + strlen(to) - 1, val + pos + strlen(from));
    res[len - 1] = 0;
    free(val);
    return (res);
}

char *set_variable(char *arg)
{
    char *val = my_strdup(arg);
    int quoted = 0;

    for (size_t i = 0; arg[i]; i++) {
        update_quoted(&quoted, arg[i]);
        if (quoted > 1) {
            i += quoted == 3;
            continue;
        }
        if (arg[i] == '$')
            val = replacing(val, i + 1);
    }
    return (val);
}