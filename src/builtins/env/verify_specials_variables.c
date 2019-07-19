/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** verif specials variables
*/

#include "shell.h"
#include "command.h"
#include "env.h"
#include "utils.h"
#include "str.h"
#include <string.h>
#include <stdio.h>

int check_value(char *value, env_t *local)
{
    if (strcmp(local->value, value) != 0)
        local->value = my_strdup(value);
    return (1);
}

int check_name(env_t *local, char *env_var)
{
    vector_t *env = get_shell()->env;
    env_t *elmt = NULL;

    for (unsigned int i = 0; i < env->size && env->elements[i]; i++) {
        elmt = (env_t *)env->elements[i];
        if (strcmp(elmt->name, env_var) == 0)
            return (check_value(elmt->value, local));
    }
    return (1);
}

int is_exist(char *argv, char *var_env)
{
    vector_t *var = get_shell()->local_var;
    env_t *local = NULL;

    for (unsigned int i = 0; i < var->size && var->elements[i]; i++) {
        local = (env_t *)var->elements[i];
        if (strcmp(argv, local->name) == 0)
            return (check_name(local, var_env));
    }
    return (0);
}

int verif_specials_variables(void)
{
    char *argv[] = {"term", "cwd", "group", "user", "home", "shlvl", NULL};
    char *var_env[] = {"TERM", "PWD", "GROUP", "USER", "HOME", "SHLVL", NULL};

    for (int i = 0; argv[i]; i++)
        is_exist(argv[i], var_env[i]);
    return (0);
}