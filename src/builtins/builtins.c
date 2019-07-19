/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** builtins
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "command.h"
#include "errors.h"
#include "vector.h"
#include "str.h"
#include "env.h"
#include "utils.h"
#include "builtins.h"
#include "alias.h"
#include "builtins_models.h"

const struct builtins_models builts[] = {
    {"history", &handle_history},
    {"cd", &my_cd},
    {"setenv", &c_setenv},
    {"unsetenv", &c_unsetenv},
    {"env", &display_env},
    {"alias", &alias},
    {"unalias", &unalias},
    {"echo", &c_echo},
    {"where", &where},
    {"which", &which},
    {"set", &local},
    {"unset", &unset},
    {"repeat", &repeat},
    {"foreach", &foreach},
    {NULL, NULL},
};

bool is_builtin(char *name)
{
    if (!strcmp(name, "exit"))
        return (true);
    if (*name == '!')
        return (true);
    for (size_t i = 0; builts[i].name; i++)
        if (!strcmp(builts[i].name, name))
            return (true);
    return (false);
}

int builtins(command_t *command, char **argv, vector_t *env)
{
    if (!strcmp(argv[0], "exit"))
        my_exit(0);
    if (*argv[0] == '!')
        return (handle_history(argv, env));
    for (size_t i = 0; builts[i].name; i++)
        if (!strcmp(builts[i].name, argv[0]))
            return (builts[i].builtin(argv, env));
    return (1);
}