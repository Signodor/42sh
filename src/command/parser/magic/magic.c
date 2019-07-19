/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** magic
*/

#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "str.h"
#include "command.h"
#include "errors.h"
#include "utils.h"

static char *final_concatene_magic(char *arg, int base,
char *content, size_t len)
{
    size_t final_len = strlen(arg) + strlen(content) - len + 1 - 2;
    char *res = my_malloc(sizeof(char) * final_len);

    memset(res, 0, final_len);
    memcpy(res, arg, base);
    memcpy(res + strlen(res), content, strlen(content));
    memcpy(res + strlen(res), arg + base + len + 2,
    strlen(arg + base + len + 2));
    free(content);
    free(arg);
    return (res);
}

static char *this_magic(char *arg, int base)
{
    char *this = NULL;
    char *start = arg + base + 1;
    size_t len = 0;

    for (; start[len] && start[len] != '`'; len++);
    if (start[len] != '`')
        return (error_ptr("Unmatched '`'."));
    this = my_malloc(sizeof(char) * (len + 1));
    memcpy(this, start, len);
    this[len] = 0;
    if (!(this = get_magic_res(this)) || !strlen(this))
        return (NULL);
    this = final_concatene_magic(arg, base, this, len);
    return (this);
}

static void magic_add_args(vector_t *args, char *arg, command_t *command)
{
    char *dupped = NULL;

    while ((dupped = dup_to_space(&arg))) {
        vector_append(args, dupped);
        command->nb_args++;
    }
}

int magic(vector_t *args, char *arg, command_t *command)
{
    char *new_arg = my_strdup(arg);
    int found = 0;

    for (size_t i = 0; new_arg[i]; i++) {
        if (new_arg[i] == '`') {
            found = 1;
            new_arg = this_magic(new_arg, i);
            i = 0;
        }
        if (!new_arg)
            return (-1);
    }
    if (found)
        magic_add_args(args, new_arg, command);
    free(new_arg);
    return (found);
}