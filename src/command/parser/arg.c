/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** word
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "str.h"
#include "errors.h"
#include "utils.h"
#include "command.h"

size_t final_len(char *arg)
{
    size_t len = 0;
    int quoted = 0;

    for (size_t i = 0; arg[i]; i++) {
        if (update_quoted(&quoted, arg[i]))
            continue;
        len++;
    }
    if (end_quote(quoted) == -1)
        return (0);
    return (len);
}

void get_res(char *arg, char *buff)
{
    int quoted = 0;
    size_t idx = 0;

    for (size_t i = 0; arg[i]; i++) {
        if (update_quoted(&quoted, arg[i]))
            continue;
        buff[idx] = arg[i];
        idx++;
    }
    buff[idx] = 0;
}

int parse_arg(vector_t *args, char *arg, command_t *command)
{
    size_t len;
    char *res = NULL;

    if (magic(args, arg, command))
        return (0);
    if (!(len = final_len(arg)))
        return (-1);
    res = my_malloc(sizeof(char) * (len + 1));
    get_res(arg, res);
    vector_append(args, res);
    command->nb_args++;
    return (0);
}