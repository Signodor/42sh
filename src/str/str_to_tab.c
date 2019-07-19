/*
** EPITECH PROJECT, 2019
** MUL_2018_my_defender
** File description:
** str
*/

#include <stdlib.h>
#include "str.h"

bool is_delimiter(char c, char *delimiters)
{
    for (size_t i = 0; delimiters[i]; i++)
        if (delimiters[i] == c)
            return (true);
    return (false);
}

char *my_strdup_escaped(char const *str, size_t length)
{
    char *res;
    size_t index = 0;
    bool escape_next = false;

    if (!str || !length)
        return (NULL);
    if (!(res = malloc(sizeof(char) * (length + 1))))
        return (NULL);
    for (size_t i = 0; i < length; i++) {
        if ((str[i] == '\"' || str[i] == '\\') && !escape_next) {
            escape_next = str[i] == '\\';
        } else if (str[i] != '\"' && str[i] != '\\' && escape_next)
            res[index++] = '\\';
        res[index++] = str[i];
        escape_next = false;
    }
    res[index] = 0;
    return (res);
}

char *my_strtok(char const **str, char *delimiters)
{
    char *ret;
    size_t size;
    bool quoted = false;
    bool escape_next = false;

    for (size = 0; (*str)[size] &&
    (!is_delimiter((*str)[size], delimiters) || quoted); size++) {
        if ((*str)[size] == '\"' && !escape_next)
            quoted = !quoted;
        if ((*str)[size] == '\\' && !escape_next)
            escape_next = true;
        else
            escape_next = false;
    }
    if (quoted)
        return (NULL);
    ret = my_strdup_escaped(*str, size);
    (*str) += size;
    return (ret);
}

char **str_to_tab(char const *str, char *delimiters)
{
    char **res;
    size_t size = 1;
    size_t i;

    for (; *str && is_delimiter(*str, delimiters); str++);
    for (i = 0; str[i]; i++)
        size += is_delimiter(str[i], delimiters) &&
        !is_delimiter(str[i + 1], delimiters) && str[i + 1];
    if (!(res = malloc(sizeof(char *) * (size + 2))))
        return (NULL);
    res++;
    for (i = 0; i < (size + 1); i++)
        res[i] = NULL;
    for (i = 0; *str && i < size; i++) {
        if (!(res[i] = my_strtok(&str, delimiters)))
            return (NULL);
        for (; (*str && is_delimiter(*str, delimiters)); str++);
    }
    res[-1] = (void *)i;
    return (res);
}

void free_str_tab(char **tab)
{
    if (!tab)
        return;
    for (size_t i = 0; tab[i]; i++)
        free(tab[i]);
    tab--;
    free(tab);
}