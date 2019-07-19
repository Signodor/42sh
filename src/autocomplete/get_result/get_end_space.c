/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_end_space
*/

#include "auto_complete_sys.h"

char *end_space(auto_complete_t *content, char *res)
{
    if (content_size(content) == 1 && res && res[strlen(res) - 1] != '/')
        res = my_strcat(res, " ");
    return (res);
}