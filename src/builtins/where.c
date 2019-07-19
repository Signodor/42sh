/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** where
*/

#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "errors.h"
#include "builtins.h"
#include "utils.h"
#include "command.h"
#include "str.h"
#include "shell.h"
#include "alias.h"

static void solo_alias(vector_t *aliases, char *arg)
{
    alias_t *alias = get_alias_name(aliases, arg);

    if (!alias)
        return;
    printf("%s is aliased to ", alias->name);
    print_alias_cmd(alias);
}

void solo_where(char *arg)
{
    char **pathes = get_paths();
    char *str;

    solo_alias(get_shell()->aliases, arg);
    if (is_builtin(arg))
        printf("%s is a shell built-in\n", arg);
    if (!pathes)
        return;
    for (size_t i = 0; pathes[i]; i++) {
        if ((str = founded(pathes[i], arg))) {
            printf("%s\n", str);
            free(str);
        }
    }
}

int where(char **argv, vector_t *env)
{
    if (!argv[1])
        return (error_param_int("where", "Too few arguments."));
    for (size_t i = 1; argv[i]; i++)
        solo_where(argv[i]);
    return (0);
}