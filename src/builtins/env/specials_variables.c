/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** specials_variables
*/

#include "shell.h"
#include "command.h"
#include "env.h"
#include "utils.h"
#include "str.h"
#include <string.h>
#include <stdio.h>

char *parse_path(char *path)
{
    char *line = malloc(sizeof(char) * (strlen(path) + 3));
    int j = 1;

    line[0] = '(';
    for (int i = 0; path[i]; i++, j++) {
        if (path[i] == ':')
            line[j] = ' ';
        else
            line[j] = path[i];
    }
    line[j++] = ')';
    line[j] = '\0';
    return (line);
}

void create_path_local(void)
{
    vector_t *env = get_shell()->env;
    vector_t *var = get_shell()->local_var;
    env_t *elmt = NULL;
    env_t *local = my_malloc(sizeof(env_t));
    char *str = NULL;

    for (unsigned int i = 0; i < env->size && env->elements[i]; i++) {
        elmt = env->elements[i];
        if (strcmp("PATH", elmt->name) == 0) {
            local->name = my_strdup("path");
            local->value = parse_path(elmt->value);
            vector_append(var, local);
            return;
        }
    }
    free(local);
}

void create_special_variable(char *var_env, char *var_local)
{
    vector_t *env = get_shell()->env;
    vector_t *var = get_shell()->local_var;
    env_t *elmt = NULL;
    env_t *local = my_malloc(sizeof(env_t));

    for (unsigned int i = 0; i < env->size && env->elements[i]; i++) {
        elmt = env->elements[i];
        if (strcmp(var_env, elmt->name) == 0) {
            local->name = my_strdup(var_local);
            local->value = my_strdup(elmt->value);
            vector_append(var, local);
            return;
        }
    }
    free(local);
}

void special_variables(void)
{
    vector_t *var = get_shell()->local_var;
    env_t *local = NULL;
    char *argv[] = {"term", "cwd", "group", "user", "home", "shlvl", NULL};
    char *var_env[] = {"TERM", "PWD", "GROUP", "USER", "HOME", "SHLVL", NULL};

    for (int i = 0; argv[i]; i++)
        if (is_exist(argv[i], var_env[i]) == 0)
            create_special_variable(var_env[i], argv[i]);
    create_path_local();
}