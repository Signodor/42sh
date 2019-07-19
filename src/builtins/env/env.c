/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** env
*/

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "errors.h"
#include "str.h"
#include "env.h"
#include "utils.h"

void disp_env(vector_t *env, char sep)
{
    env_t *menv;
    char buff[1024];

    for (size_t i = 0; i < env->size && env->elements[i]; i++) {
        menv = (env_t *)env->elements[i];
        printf("%s%c", menv->name, sep);
        if (menv->value)
            printf("%s", menv->value);
        printf("\n");
    }
}

void set_env(vector_t *vec, char *name, char *value)
{
    env_t *env;
    size_t i;
    char found = 0;

    if (!name || !value)
        return;
    for (i = 0; i < vec->size && vec->elements[i] && !found; i++) {
        env = (env_t *)vec->elements[i];
        if (strcmp(env->name, name) == 0) {
            free(env->value);
            env->value = value;
            found = 1;
        }
    }
    if (!found) {
        env = my_malloc(sizeof(env_t));
        env->name = name;
        env->value = value;
        vector_append(vec, env);
    }
}

void unset_env(vector_t *vec, char *name)
{
    env_t *env;

    for (size_t i = 0; i < vec->size && vec->elements[i]; i++) {
        env = (env_t *)vec->elements[i];
        if (strcmp(env->name, name) == 0) {
            vector_pop_this(vec, env);
            free(env->name);
            free(env->value);
            break;
        }
    }
}

char *get_env(vector_t *vec, char *name)
{
    env_t *env;

    for (size_t i = 0; i < vec->size && vec->elements[i]; i++) {
        env = (env_t *)vec->elements[i];
        if (strcmp(env->name, name) == 0)
            return (env->value);
    }
    errno = 2;
    return (NULL);
}

char **get_envp(vector_t *vec)
{
    char **envp = calloc(vec->size + 1, sizeof(char *));
    env_t *env;
    int index = 0;

    check_ptr(envp);
    for (size_t i = 0; i < vec->size && vec->elements[i]; i++) {
        env = (env_t *)vec->elements[i];
        envp[index] =
        calloc(strlen(env->name) + strlen(env->value) + 2, 1);
        strcpy(envp[index], env->name);
        envp[index][strlen(env->name)] = '=';
        strcpy(envp[index] + strlen(env->name) + 1, env->value);
        envp[index][strlen(env->name) + strlen(env->value) + 1] = 0;
        index++;
    }
    return (envp);
}