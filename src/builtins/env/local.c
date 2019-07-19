/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** local
*/

#include "builtins.h"
#include "env.h"
#include "shell.h"

int local(char **argv, vector_t *env)
{
    vector_t *local_var = get_shell()->local_var;

    if (!argv[1]) {
        disp_env(local_var, '\t');
        return (0);
    }
    return (c_setenv(argv, local_var));
}

int unset(char **argv, vector_t *env)
{
    vector_t *local_var = get_shell()->local_var;

    return (c_unsetenv(argv, local_var));
}