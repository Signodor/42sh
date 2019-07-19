/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** line
*/

#include <unistd.h>
#include <string.h>
#include "str.h"
#include "vector.h"
#include "utils.h"
#include "history.h"
#include "shell.h"
#include "linked.h"
#include <stdio.h>

char *get_line_res(vector_t *vec)
{
    char *res;
    size_t len = 1;
    size_t idx = 0;

    for (size_t i = 0; i < vec->size; i++)
        len += strlen((char *)vec->elements[i]) + 1;
    len -= len > 1 ? 1 : 0;
    res = my_malloc(sizeof(char) * len);
    for (size_t i = 0; i < vec->size; i++) {
        strcpy(res + idx, (char *)vec->elements[i]);
        idx += strlen((char *)vec->elements[i]);
        if (i < vec->size - 1)
            res[idx++] = ' ';
    }
    res[idx] = '\0';
    return (res);
}

int check_parenthesis(char *line)
{
    int par = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '(' && (i == 0 || line[i - 1] != '\\'))
            par++;
        if (line[i] == ')' && (i == 0 || line[i - 1] != '\\'))
            par--;
        if (par < 0) {
            fprintf(stderr, "Too many )'s.\n");
            return (1);
        }
    }
    if (par) {
        fprintf(stderr, "Too many ('s.\n");
        return (1);
    }
    return (0);
}

char *clean_line(char *line)
{
    wordent_t *wordent = NULL;
    char *clean = NULL;
    char *arg;
    int status = 0;

    if (check_parenthesis(line))
        return (NULL);
    while ((arg = get_arg(&line, &status)) && !status) {
        wordent = linked_append(wordent, arg);
        if (set_aliases(&wordent))
            return (NULL);
    }
    if (!(clean = linked_concaten(wordent)))
        return (NULL);
    linked_free(wordent);
    if (status)
        return (NULL);
    return (clean);
}

char **parse_line(char *line, bool add)
{
    char **tab;
    char *res = clean_line(line);

    if (!res)
        return (NULL);
    if (*res != '!' && get_shell()->histo_up && add)
        add_histo(res, get_shell()->history);
    tab = str_to_tab(res, ";");
    free(res);
    return (tab);
}