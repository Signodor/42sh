/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** arguments
*/

#include <stdio.h>
#include "command.h"
#include "str.h"
#include "vector.h"
#include "control.h"
#include "errors.h"
#include "env.h"
#include "utils.h"

void clean_vec(vector_t *vec)
{
    for (size_t i = 0; i < vec->size; i++)
        free(vec->elements[i]);
    vector_delete(vec);
}

void end_arg(command_t *command, vector_t *vec)
{
    char **tab;

    if (!(tab = malloc(sizeof(char *) * (vec->size + 1))))
        my_exit(84);
    for (size_t i = 0; i < vec->size; i++)
        tab[i] = vec->elements[i];
    tab[vec->size] = NULL;
    vector_delete(vec);
    command->arguments = tab;
}

int handle_arg(command_t *command, char **content, char *arg, vector_t *vec)
{
    char *arg_ok = set_variable(arg);
    int status = __INT32_MAX__ - 1;

    if (is_control(arg_ok))
        status = call(command, content, arg_ok);
    if (is_globable(vec, arg_ok))
        status = glob_arg(command, vec, arg_ok);
    if (status == __INT32_MAX__ - 1)
        status = parse_arg(vec, arg_ok, command);
    free(arg_ok);
    return (status);
}

int get_arguments(command_t *command, char **content)
{
    vector_t *vec = vector_create();
    struct control control;
    char *arg;
    int status = 0;

    while ((arg = get_arg(content, &status))) {
        if (handle_arg(command, content, arg, vec)) {
            free(arg);
            clean_vec(vec);
            return (-1);
        }
        free(arg);
    }
    end_arg(command, vec);
    if (!command->nb_args)
        return (error_int(NULL_COMMAND));
    return (0);
}