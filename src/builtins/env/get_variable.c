/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_variable
*/

#include <string.h>
#include "shell.h"
#include "errors.h"
#include "env.h"

char *look(char *name, vector_t *list)
{
    env_t *env;

    for (size_t i = 0; i < list->size; i++) {
        env = (env_t *)list->elements[i];
        if (!strcmp(env->name, name))
            return (env->value);
    }
    return (NULL);
}

char *get_variable_value(char *name)
{
    shell_t *shell = get_shell();
    char *value;

    if (!name)
        return (NULL);
    if ((value = look(name, shell->local_var)))
        return (value);
    if ((value = look(name, shell->env)))
        return (value);
    error_msg(name, "Undefined variable.");
    return (NULL);
}