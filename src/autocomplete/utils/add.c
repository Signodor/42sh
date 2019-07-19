/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** add
*/

#include "auto_complete_sys.h"

content_t *new_content(char *name)
{
    content_t *new = malloc(sizeof(content_t));

    new->name = name;
    new->type = 0;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}