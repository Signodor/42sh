/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** All ctrl operation
*/

#include "proto_ncurse.h"
#include "utils.h"

letter_t *ctrl_all(unsigned char *buff, info_t *info, letter_t *letter,
letter_t *keep)
{
    char *tmp[2] = {0};
    int line = get_row();

    if (buff[0] == 12) {
        write(1, my_k, 4);
        for (int i = 0; i < line; i++)
            write(1, backn_clear, 5);
        for (int i = 0; i < line; i++)
            write(1, before, 3);
        if (displaying(info, letter, 1) && info->first)
            write(1, "\b", 1);
        return (letter);
    }
    return (letter);
}