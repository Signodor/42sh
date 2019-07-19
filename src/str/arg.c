/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** arg
*/

#include <string.h>
#include <stdio.h>
#include "str.h"
#include "errors.h"

size_t arg_len(char *str, int *status)
{
    int quoted = 0;
    size_t len = 0;
    int subst = 0;

    while (str[len] && (!is_control(str + len) || quoted || subst) &&
    (!is_escape(str[len]) || quoted || subst)) {
        if (!update_quoted(&quoted, str[len]))
            subst = str[len] == '`' ? !subst : subst;
        len++;
    }
    if (subst)
        error_msg("Parser", "Unmatched '`'.");
    if (end_quote(quoted) || subst) {
        (*status) = 1;
        return (0);
    }
    return (len);
}

char *get_arg(char **content, int *status)
{
    char *res;
    size_t len;

    skip_escape(content);
    if (is_control(*content)) {
        res = dup_control(*content);
        (*content) += strlen(res);
        return (res);
    }
    if (!(len = arg_len(*content, status)))
        return (NULL);
    res = my_strndup(*content, len);
    (*content) += len;
    return (res);
}