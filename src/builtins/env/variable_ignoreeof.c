/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** ignoreeof
*/

#include "shell.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_value_ignoreeof_bis(int value)
{
    if (get_shell()->ignoreeof < value) {
        get_shell()->ignoreeof++;
        printf("\nUse \"exit\" to leave 42sh.\n");
        display_line(false, 0);
    } else
        return (1);
    return (0);
}

int check_value_ignoreeof(env_t *local)
{
    int value = atoi(local->value);

    if (value < 0)
        return (1);
    else if (value == 0) {
        printf("\nUse \"exit\" to leave 42sh.\n");
        display_line(false, 0);
    }
    else
        return (check_value_ignoreeof_bis(value));
    return (0);
}

int ignoreeof(void)
{
    vector_t *var = get_shell()->local_var;
    env_t *local = NULL;

    for (unsigned int i = 0; i < var->size && var->elements[i]; i++) {
        local = (env_t *)var->elements[i];
        if (strcmp("ignoreeof", local->name) == 0) {
            return (check_value_ignoreeof(local));
        }
    }
    return (1);
}