/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** prototype ncurses
*/

#include "proto_ncurse.h"
#include "utils.h"
#include <term.h>
#include "shell.h"
#include "env.h"

void move_cursor_interline(unsigned char *tmp, int cond, letter_t *act,
info_t *info)
{
    int cursor = cursor_pos(-1);
    int col = get_col();

    if (tmp[1] == 'D' && cond)
        cursor_pos(cursor - 1);
    if (tmp[1] == 'C' && cond)
        cursor_pos(cursor + 1);
    if (cond && tmp[1] == 'D' && !((cursor) % col)) {
        write(1, before, 4);
        for (int x = 0; x <= col; x++)
            write(1, after, 3);
    }
    if (cond && tmp[1] == 'C' && !((cursor + 1) % col)) {
        write(1, down, 3);
        write(1, "\r", 1);
    }
}

int max_characters(unsigned char *buff, letter_t *act, info_t *info)
{
    int i = 0;
    int cond = 1;
    unsigned char tmp[3] = {0};
    static int im_null = 1;

    read(0, tmp, 2);
    if (tmp[1] == 72)
        return (-1);
    if (tmp[1] != 'D' && tmp[1] != 'C')
        return (tmp[1] == 'A' || tmp[1] == 'B' ? tmp[1] : 0);
    im_null *= !act;
    im_null = act && !act->prev ? 1 : im_null;
    cond *= !((tmp[1] == 'D' && !act) || (tmp[1] == 'C' && act && !act->next));
    cond *= !(tmp[1] == 'C' && !act && (!im_null || !info->first));
    cond = (tmp[1] == 'C' && !act && info->first) ? 1 : cond;
    write(1, buff, cond);
    write(1, tmp, 2 * cond);
    move_cursor_interline(tmp, cond, act, info);
    return (cond ? tmp[1] : 0);
}

letter_t *have_to_continue(unsigned char *buff, info_t *info,
letter_t *letter, letter_t *keep)
{
    int clr;
    int col = get_col();

    if (buff[0] == 127)
        return (delete_chr(letter, info, keep));
    if ((buff[0] == 27) && (clr = max_characters(buff, letter, info))) {
        if (clr != -1)
            return (move_cursor(letter, clr, info));
        for (int i = cursor_pos(-1); i >= col; i -= col)
            write(1, before, 3);
        cursor_pos(display_line(false, 84));
        if (displaying(info, NULL, 0))
            write(1, "\b", 1);
        cursor_pos(display_line(false, 84));
        return (NULL);
    }
    return (letter);
}

letter_t *use_the_read(unsigned char *buff, letter_t *letter, info_t *info,
letter_t *keep)
{
    if (buff[0] == 9 || (buff[0] == 4 && info->first))
        return (transform_to_linked(info, letter, buff[0]));
    if (buff[0] >= 0 && buff[0] < 27)
        return (ctrl_all(buff, info, letter, keep));
    letter = have_to_continue(buff, info, letter, keep);
    if (buff[0] == 127 || buff[0] == 27 || buff[0] == 4)
        return (letter);
    letter = choose_init(letter, info, buff[0]);
    displaying(info, keep, 0);
    return (letter);
}

char *prototype_ncurse(void)
{
    unsigned char buff[2] = {0};
    info_t *info = define_info(false);
    letter_t *letter = NULL;
    letter_t *keep = NULL;

    for (info->first = NULL; buff[0] != '\r'; keep = letter) {
        read(0, buff, 1);
        if (!info->first && letter)
            letter = NULL;
        if (buff[0] == 0 || (buff[0] == 4 && !info->first && ignoreeof()))
            return (free_letters(info));
        if (buff[0] == 10 || buff[0] == '\r')
            return (convert_all(info, 1));
        letter = use_the_read(buff, letter, info, keep);
    }
    return (NULL);
}