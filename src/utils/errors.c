/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** errors
*/

#include <stdio.h>
#include "errors.h"

void error_msg(char const *att, char const *msg)
{
    fprintf(stderr, "%s: %s\n", att, msg);
}

int error_int(char const *msg)
{
    error_msg(NAME, msg);
    return (-1);
}

void *error_ptr(char const *msg)
{
    error_msg(NAME, msg);
    return (NULL);
}

int error_param_int(char const *att, char const *msg)
{
    error_msg(att, msg);
    return (-1);
}
