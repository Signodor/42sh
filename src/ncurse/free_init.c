/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** free/init ncurses
*/

#include "proto_ncurse.h"
#include "utils.h"

char *free_letters(info_t *info)
{
    letter_t *del = NULL;

    for (letter_t *tmp = info->first; tmp; del = NULL) {
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
    info->first = NULL;
    info->is_new = 1;
    return (NULL);
}

letter_t *choose_init(letter_t *prev, info_t *info, int buff)
{
    letter_t *letter = my_malloc(sizeof(letter_t));

    letter->ascii = buff;
    letter->next = NULL;
    letter->prev = prev;
    if (info->first && !prev)
        letter->next = info->first;
    if (prev && prev->next)
        letter->next = prev->next;
    if (letter && letter->next)
        letter->next->prev = letter;
    if (prev)
        prev->next = letter;
    if (!prev)
        info->first = letter;
    return (letter);
}

letter_t *link_letter(info_t *info, letter_t *letter)
{
    if (letter->prev)
        letter->prev->next = letter->next;
    if (letter->next)
        letter->next->prev = letter->prev;
    if (letter == info->first)
        info->first = letter->next;
    if (letter != info->first)
        letter = letter->prev;
    return (letter);
}

letter_t *delete_chr(letter_t *letter, info_t *info, letter_t *keep)
{
    letter_t *tmp = letter;
    static int cond = 0;

    if (!letter)
        return (NULL);
    letter = link_letter(info, letter);
    if (!cond && letter && letter->ascii > 127 && tmp && tmp->ascii > 127) {
        cond = 1;
        letter = delete_chr(letter, info, keep);
    }
    free(tmp);
    cursor_pos(cursor_pos(-1) - 1);
    if (displaying(info, letter, 2) && info->first)
        write(1, "\b", 1);
    cond = 0;
    return (letter);
}

info_t *define_info(bool delete)
{
    static info_t *info = NULL;

    if (!info) {
        info = my_malloc(sizeof(info_t));
        info->first = NULL;
        info->is_new = 1;
    }
    if (delete)
        free(info);
    return (info);
}