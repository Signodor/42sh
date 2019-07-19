/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** quoted
*/

#include <stdio.h>
#include "str.h"
#include "errors.h"

int quoted_type(char c)
{
    switch (c) {
        case '"':
            return (1);
        case '\'':
            return (2);
        case '\\':
            return (3);
    }
    return (0);
}

int update_quoted(int *quoted, char c)
{
    if (!*quoted) {
        if (!quoted_type(c))
            return (0);
        *quoted = quoted_type(c);
        return (1);
    }
    if (*quoted == quoted_type(c) && *quoted != 3) {
        *quoted = 0;
        return (1);
    }
    if (*quoted == 3)
        *quoted = 0;
    return (0);
}

int end_quote(int quoted)
{
    char pb = 0;

    if (!quoted)
        return (0);
    pb = quoted == 1 ? '"' : pb;
    pb = quoted == 2 ? '\'' : pb;
    pb = quoted == 3 ? '\\' : pb;
    fprintf(stderr, "%s: Unmatched '%c'.\n", NAME, pb);
    return (-1);
}