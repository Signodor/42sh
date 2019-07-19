/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** getter
*/

#include <string.h>
#include "alias.h"

alias_t *get_alias_name(vector_t *aliases, char *name)
{
    alias_t *alias;

    for (size_t i = 0; i < aliases->size; i++) {
        alias = aliases->elements[i];
        if (!strcmp(alias->name, name))
            return (alias);
    }
    return ((alias_t *)NULL);
}