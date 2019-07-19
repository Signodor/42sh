/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** word
*/

#include <string.h>
#include <stdbool.h>
#include "str.h"
#include "errors.h"
#include "utils.h"

bool is_escape(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

void skip_escape(char **content)
{
    if (!content || !(*content))
        return;
    for (; **content && is_escape(**content); (*content)++);
}

bool empty_line(char *content)
{
    skip_escape(&content);
    return (*content == 0);
}

char *get_next_word(char *arg)
{
    char *buffer;
    size_t len = 0;

    for (len = 0; my_char_isalphanumeric(arg[len]); len++);
    if (!len)
        return (error_ptr(ENVNAME));
    buffer = my_malloc(sizeof(char) * (len + 1));
    for (size_t i = 0; i < len; i++)
        buffer[i] = arg[i];
    buffer[len] = 0;
    return (buffer);
}

char *dup_to_space(char **content)
{
    char *buffer;
    size_t len = 0;

    skip_escape(content);
    for (len = 0; (*content)[len] && !is_escape((*content)[len]); len++);
    if (!len)
        return (NULL);
    buffer = my_malloc(sizeof(char) * (len + 1));
    memcpy(buffer, *content, len);
    buffer[len] = 0;
    (*content) += len;
    return (buffer);
}