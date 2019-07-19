/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** convert to string
*/

#include "proto_ncurse.h"
#include "auto_complete.h"
#include "utils.h"
#include "shell.h"

char *convert_all(info_t *info, bool cond)
{
    char *final = NULL;
    int i = 0;
    int v = -1;
    int x = 0;
    int pos = cursor_pos(-1);

    for (letter_t *tmp = info->first; tmp; tmp = tmp->next)
        i++;
    final = malloc(i + 1);
    skip_my_lines(info->first, cond);
    for (letter_t *tmp = info->first; tmp; tmp = tmp->next)
        final[++v] = tmp->ascii;
    final[++v] = 0;
    if (cond) {
        free_letters(info);
        write(1, "\n", 1);
    }
    return (final);
}

char *to_be_completed(info_t *info, letter_t *act)
{
    char *final = NULL;
    int i = 0;
    int v = -1;
    letter_t *tmp = info->first;

    for (; tmp && act && tmp->prev != act; tmp = tmp->next)
        i++;
    final = malloc(i + 1);
    for (tmp = info->first; tmp && act && tmp->prev != act; tmp = tmp->next)
        final[++v] = tmp->ascii;
    final[++v] = 0;
    return (final);
}

letter_t *transform_to_linked(info_t *info, letter_t *act, int cond)
{
    int i = 0;
    letter_t *tmp = info->first;
    char *start = to_be_completed(info, act);
    char *final = auto_complete(start, cond == 4);
    int col = get_col();
    bool c = move_auto_completion(-1);

    if (!final || !start)
        return (act);
    for (; start[i] && final[i]; i++);
    for (; final[i]; i++)
        act = choose_init(act, info, final[i]);
    free(start);
    free(final);
    for (int b = i + display_line(false, 84); c && b >= col; b -= col)
        write(1, "\n", 1);
    displaying(info, act ? act->prev : NULL, 0);
    return (act);
}