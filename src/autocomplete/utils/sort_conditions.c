/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sort_conditions
*/

#include "auto_complete_sys.h"

int sort_conditions(char *curr, char *next, int i, int k)
{
    int curr_add = 0;
    int next_add = 0;

    if (curr[i] >= 'A' && curr[i] <= 'Z')
        curr_add = 32;
    if (next[k] >= 'A' && next[k] <= 'Z')
        next_add = 32;
    if (curr[i] + curr_add > next[k] + next_add)
        return (1);
    return (0);
}

int sort_break_condition(char *curr, char *next, int i, int k)
{
    int curr_add = 0;
    int next_add = 0;

    if (curr[i] >= 'A' && curr[i] <= 'Z')
        curr_add = 32;
    if (next[k] >= 'A' && next[k] <= 'Z')
        next_add = 32;
    if (curr[i] + curr_add < next[k] + next_add)
        return (1);
    return (0);
}