/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history_utils
*/

#include "vector.h"
#include "str.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "history.h"
#include "shell.h"
#include "command.h"

void clean_histo(vector_t *histo)
{
    histo_cmd_t *cmd;

    for (int i = histo->size - 1; i >= 0; i--) {
        cmd = histo->elements[i];
        free(cmd->cmd);
        free(cmd);
        vector_pop_at(histo, i);
    }
}

void print_histo(vector_t *histo, char *args)
{
    char *res = my_malloc(sizeof(char *) * 6);
    struct tm lt;
    int s = args[ARG_R] ? histo->size - 1 : (int)histo->size -
    (args[ARG_NB] ? args[ARG_NB] : 100) >= 0 ? histo->size -
    (args[ARG_NB] ? args[ARG_NB] : 100) : 0;
    int e = args[ARG_NB] ? args[ARG_R] ? s - args[ARG_NB] >= -1 ?
    s - args[ARG_NB] : -1 : s + (int)args[ARG_NB] : args[ARG_R] ?
    s - 100 >= -1 ? s - 100 : -1 : (int)histo->size;

    if (!args[ARG_H])
        for (int i = s; s < e ? i < e : i > e; i += s > e ? -1 : 1) {
            localtime_r(&((histo_cmd_t *)histo->elements[i])->time, &lt);
            strftime(res, sizeof(res), "%k:%M", &lt);
            printf("%6d  %s\t%s\n", ((histo_cmd_t *)histo->elements[i])->id,
            *res == ' ' ? res + 1 : res,
            ((histo_cmd_t *)histo->elements[i])->cmd);
        }
    else
        for (int i = s; s < e ? i < e : i > e; i += s > e ? -1 : 1)
            printf("%s\n", ((histo_cmd_t *)histo->elements[i])->cmd);
    my_free(res);
}

void add_histo(char *str, vector_t *histo)
{
    histo_cmd_t *cmd = my_malloc(sizeof(histo_cmd_t));
    static int nb = 1;

    if (!str)
        return;
    skip_escape(&str);
    if (!strcmp(str, ""))
        return;
    cmd->cmd = my_strdup(str);
    cmd->time = time(NULL);
    cmd->id = nb;
    vector_append(histo, cmd);
    nb++;
}