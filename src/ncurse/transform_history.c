/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** transform history array
*/

#include "shell.h"
#include "proto_ncurse.h"
#include "utils.h"

void reset_writing(int col, int c, int i, int cursor)
{
    long size = display_line(false, 84);
    int cond = 0;

    for (int b = (-i) + size - cursor; b >= col && ++cond; b -= col)
        write(1, "\e[B\r\e[K", 7);
    if (!cond)
        write(1, my_k, 4);
    for (int v = c - size; c < 0 && !cond && v <= -col; v += col)
        write(1, "\e[A\r\e[K", 7);
    for (int v = c - size; c < 0 && !cond && v <= -col; v += col)
        write(1, down, 3);
    if (cond && ((-i) + size - cursor) % col > size)
        write(1, erase_nl, 10);
    for (int b = (-i) + size - cursor; b >= col; b -= col)
        write(1, before, 3);
}

int find_good_nb(info_t *info)
{
    bool cond = 0;
    int v = 0;

    info->is_new = 0;
    for (letter_t *tmp = info->first; tmp; tmp = tmp->next) {
        if (!cond && tmp->ascii > 127 && tmp->next && tmp->next->ascii > 127)
            cond = 1;
        else
            v += !(cond = 0);
    }
    return (v);
}

letter_t *transform_history(info_t *info, char *final)
{
    letter_t *act = NULL;
    int c = 0;
    bool cond = 0;

    for (letter_t *tmp = info->first; tmp; act = NULL) {
        act = tmp;
        if (!cond && tmp->ascii > 127 && tmp->next && tmp->next->ascii > 127)
            cond = 1;
        else
            c -= !(cond = 0);
        tmp = tmp->next;
        free(act);
    }
    info->first = NULL;
    for (int i = 0; final && final[i]; i++)
        act = choose_init(act, info, final[i]);
    reset_writing(get_col(), find_good_nb(info) + c, c, cursor_pos(-1));
    free(final);
    displaying(info, act ? act->prev : NULL, 1);
    return (act);
}