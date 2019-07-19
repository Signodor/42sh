/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** deconstructor
*/

#include <string.h>
#include <errno.h>
#include "errors.h"
#include "str.h"
#include "env.h"
#include "utils.h"

vector_t *env_create(char *envp[])
{
    vector_t *list = vector_create();
    env_t *env;
    int where;

    for (size_t i = 0; envp[i]; i++) {
        env = my_malloc(sizeof(env_t));
        env->name = my_strdup_toch(envp[i], '=');
        where = strlen(env->name);
        if (envp[i][where] != '=')
            return (error_ptr(BADENV));
        env->value = my_strdup(envp[i] + where + 1);
        check_ptr(env->value);
        vector_append(list, env);
    }
    return (list);
}

void env_destroy(vector_t *list)
{
    env_t *env;

    if (!list)
        return;
    for (size_t i = 0; i < list->size; i++) {
        env = (env_t *)list->elements[i];
        free(env->name);
        free(env->value);
        free(env);
    }
    vector_delete(list);
}