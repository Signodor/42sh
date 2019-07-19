/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cursor ncurses
*/

#include "proto_ncurse.h"
#include "utils.h"
#include "shell.h"

letter_t *display_char(int col, letter_t *tmp, long *c, int reset)
{
    int pos = cursor_pos(-1);
    letter_t *last = tmp;

    for (int nb = pos; nb; nb--)
        if ((reset == 2 && !((nb + 1) % col) && nb == pos) || !(nb % col)) {
            write(1, before, 3);
        }
    *c = display_line(false, 0);
    for (bool cond = 0; tmp; tmp = tmp->next) {
        write(1, (char []){tmp->ascii, 0}, 1);
        if (!cond && tmp->ascii > 127 && tmp->next && tmp->next->ascii > 127) {
            cond = 1;
            continue;
        } else if (!((++*c) % col))
            write(1, " \b\e[K", 5);
        cond = 0;
        if (!tmp->next)
            break;
    }
    return (tmp);
}

int to_previous_line(int *cond, int *nb, long *c, int reset)
{
    if ((*cond == 1 || (!*cond && nb[0] < 127)) &&
    !((*c + (reset != 2)) % nb[1])) {
        write(1, before, 3);
        for (int x = 0; x <= nb[1]; x++)
            write(1, after, 3);
        *cond = 3;
        return (1);
    }
    return (0);
}

int comeback_cursor(long *c, int previous, int reset, letter_t *last)
{
    static int i = 0;
    static int cond = 0;
    static int nb[2] = {0};

    if (last && !last->next) {
        cond = 0;
        i = 0;
        nb[0] = last->ascii;
        nb[1] = get_col();
    }
    if ((*c - 1 < previous) && to_previous_line(&cond, nb, c, reset))
        i *= (reset != 2);
    else if (i++ > 0 && cond != 2)
        write(1, "\b", 1);
    if (--*c > -2 && cond != 2 && last->ascii > 127 &&
    last->prev && last->prev->ascii > 127 && ++*c > -2) {
        cond = 2 + (cond == 3);
    } else if (cond != 3)
        cond = 1;
    return (cond);
}

int displaying(info_t *info, letter_t *keep, int reset)
{
    int cond = 0;
    static int previous = 0;
    int pos = cursor_pos(-1);
    long c = 0;
    letter_t *last = display_char(get_col(), info->first, &c, reset);
    long r = c;

    if ((!keep && info->first && !info->first->next) || reset == 1)
        previous = cursor_pos(display_line(false, 84));
    for (; last && last != keep; last = last->prev)
        cond = comeback_cursor(&c, previous, reset, last);
    previous = r;
    cursor_pos(c - (cond == 2) + (reset != 2));
    return (reset == 2 && cond >= 2 ? 0 : cond);
}