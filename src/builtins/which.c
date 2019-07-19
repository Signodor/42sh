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

static int which_solo_alias(vector_t *aliases, char *arg)
{
    alias_t *alias = get_alias_name(aliases, arg);

    if (!alias)
        return (0);
    printf("%s: \t aliased to ", alias->name);
    print_alias_cmd(alias);
    return (1);
}

void solo_which(char *arg)
{
    char **pathes = get_paths();
    char *str;

    if (which_solo_alias(get_shell()->aliases, arg))
        return;
    if (is_builtin(arg)) {
        printf("%s: shell built-in command.\n", arg);
        return;
    }
    if (!pathes)
        return;
    for (size_t i = 0; pathes[i]; i++) {
        if ((str = founded(pathes[i], arg))) {
            printf("%s\n", str);
            free(str);
            return;
        }
    }
    fprintf(stderr, "%s: Command not found.\n", arg);
}

int which(char **argv, vector_t *env)
{
    if (!argv[1])
        return (error_param_int("which", "Too few arguments."));
    for (size_t i = 1; argv[i]; i++)
        solo_which(argv[i]);
    return (0);
}