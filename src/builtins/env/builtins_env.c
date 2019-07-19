/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** builtins_env
*/

#include <string.h>
#include "env.h"
#include "utils.h"
#include "errors.h"
#include "vector.h"
#include "str.h"

int display_env(char **argv, vector_t *env)
{
    disp_env(env, '=');
    return (0);
}

int c_unsetenv(char **argv, vector_t *env)
{
    env_t *envel;

    if (!argv[1])
        return (error_int("Error : too few arguments."));
    if (!strcmp(argv[1], "*")) {
        while ((envel = vector_pop(env))) {
            free(envel->name);
            free(envel->value);
            free(envel);
        }
    } else
        unset_env(env, argv[1]);
    return (0);
}

int c_setenv(char **argv, vector_t *env)
{
    if (!argv[1])
        display_env(argv, env);
    else {
        if (!my_char_isalphanumeric(*argv[1]))
            return (error_int(SETENV_BEGIN));
        if (!my_str_isalphanumeric(argv[1]))
            return (error_int(ENVNAME));
        if (!argv[2])
            set_env(env, my_strdup(argv[1]), my_strdup(""));
        else
            set_env(env, my_strdup(argv[1]), my_strdup(argv[2]));
    }
    return (0);
}