/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history
*/

#ifndef HISTORY_H_
#define HISTORY_H_

#include "typedefs.h"
#include <time.h>

struct histo_cmd
{
    time_t time;
    char *cmd;
    int id;
};

enum arg_histo_e
{
    ARG_H,
    ARG_C,
    ARG_R,
    ARG_NB,
};

void add_histo(char *cmd, vector_t *histo);
void print_histo(vector_t *histo, char *args);
void clean_histo(vector_t *histo);
char *get_cmd_histo(vector_t *histo, char *cmd);
char *move_in_histo(bool dir, char *old, bool is_new);

#endif /* !HISTORY_H_ */