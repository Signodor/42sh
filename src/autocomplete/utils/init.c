/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** init
*/

#include "auto_complete_sys.h"

auto_complete_t *init_auto_complete(void)
{
    auto_complete_t *res = malloc(sizeof(auto_complete_t));

    res->content = NULL;
    res->size = 0;
    return (res);
}