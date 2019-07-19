/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** replace the cursor after a cmd
*/

#include "utils.h"
#include "proto_ncurse.h"
#include "shell.h"
#include "history.h"

void skip_my_lines(letter_t *tmp, bool newline)
{
    int b = display_line(false, 84);
    int col = get_col();
    int i = 0;

    if (!tmp)
        return;
    for (bool cond = 0; tmp; tmp = tmp->next) {
        if (!cond && tmp->ascii > 127 && tmp->next && tmp->next->ascii > 127) {
            cond = 1;
            continue;
        }
        cond = 0;
        i++;
    }
    for (int var = cursor_pos(-1); newline && var < (i + b); var++)
        if (!((var + 1) % col))
            write(1, down, 3);
}

int cursor_pos(int pos)
{
    static int my_pos = 0;

    if (pos >= 0)
        my_pos = pos;
    return (my_pos);
}

int get_previous(int reset)
{
    static int last_cmd = 0;

    if (reset == -1)
        return (last_cmd);
    if (reset == 2)
        last_cmd = 1;
    else
        last_cmd = 0;
    return (last_cmd);
}

letter_t *move_cursor(letter_t *act, int chr, info_t *info)
{
    char *new;

    if (chr == 'A' || chr == 'B') {
        new = move_in_histo(chr == 'A', convert_all(info, 0), info->is_new);
        return (transform_history(info, new));
    } else if (chr == 'C' && !act) {
        if (info->first && info->first->next && info->first->ascii > 127)
            return (info->first->next);
        return (info->first);
    }
    if (chr == 'C' && act && act->next) {
        act = act->next;
        if (act && act->next && act->next->ascii > 127 && act->ascii > 127)
            act = act->next;
    } else if (chr == 'D' && act) {
        if (act && act->prev && act->prev->ascii > 127 && act->ascii > 127)
            act = act->prev;
        act = act->prev;
    }
    return (act);
}