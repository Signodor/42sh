/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** proto_ncurse
*/

#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

/*Proto ncurses */

typedef struct letter_s letter_t;

struct letter_s
{
    letter_t *next;
    letter_t *prev;
    unsigned ascii;
};

typedef struct str_s
{
    char *str;
    bool move;
} str_t;

typedef struct info_s
{
    letter_t *first;
    bool is_new;
} info_t;

static char const back[] = {27, 91, 68, 0};
static char const after[] = {27, 91, 67, 0};
static char const before[] = {27, 91, 'A', 0};
static char const down[] = {27, 91, 'B', 0};
static char const ctrl_e[] = {27, 91, 'F', 0};

static char const erase_nl[] = {27, 91, 66, 13, 27, 91, 75, 27, 91, 65, 0};
static char const my_k[] = {'\r', 27, 91, 'K', 0};
static char const backn_clear[] = {'\n', '\r', 27, 91, 'K', 0};
static char const ctrl_k[] = {27, 91, 'K', 0};
static char const del[] = {127, 0};

char *prototype_ncurse(void);
char *free_letters(info_t *info);
letter_t *move_cursor(letter_t *letter, int chr, info_t *info);
letter_t *delete_chr(letter_t *letter, info_t *info, letter_t *keep);
char *convert_all(info_t *info, bool cond);
letter_t *choose_init(letter_t *prev, info_t *info, int buff);
int displaying(info_t *info, letter_t *keep, int reset);
char *to_be_completed(info_t *info, letter_t *act);
letter_t *transform_to_linked(info_t *info, letter_t *act, int cond);
info_t *define_info(bool delete);
int cursor_pos(int pos);
letter_t *transform_history(info_t *info, char *new);
letter_t *ctrl_all(unsigned char *buff, info_t *, letter_t *, letter_t *keep);
void skip_my_lines(letter_t *, bool newline);
int get_previous(int reset);
