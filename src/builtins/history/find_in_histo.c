/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** find_in_histo
*/

#include "vector.h"
#include "str.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "history.h"

int is_all_number(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return (1);
    return (0);
}

char *find_in_histo(vector_t *histo, char *cmd)
{
    int is_after = cmd[strlen(cmd) - 1] == '?';
    char *find;

    for (int i = histo->size - 1; i >= 0; i--) {
        find = strstr(((histo_cmd_t *)histo->elements[i])->cmd,
        my_str_replace(cmd, "?", ""));
        if (find && (((!is_after && *(find +
        strlen(my_str_replace(cmd, "?", ""))) == '\0')) || is_after))
            return (((histo_cmd_t *)histo->elements[i])->cmd);
    }
    free(find);
    return (NULL);
}

char *get_cmd_from_str(vector_t *histo, char *cmd)
{
    char **tmp;

    if (*cmd == '?')
        return (find_in_histo(histo, cmd));
    if (*cmd == '^' && histo->size) {
        tmp = str_to_tab(cmd + 1, "^");
        if (!tmp[0])
            return (NULL);
        return (my_str_replace(
        ((histo_cmd_t *)histo->elements[histo->size - 1])->cmd,
        tmp[0], tmp[1]));
    }
    for (int i = histo->size - 1; i >= 0; i--)
        if (!strncmp(((histo_cmd_t *)histo->elements[i])->cmd, cmd,
        strlen(cmd)))
            return (my_strdup(((histo_cmd_t *)histo->elements[i])->cmd));
    return (NULL);
}

char *get_cmd_histo_two(vector_t *histo, char *cmd, int pos)
{
    char *ret;

    if (pos >= (int)histo->size) {
        fprintf(stderr, "%d: Event not found\n", pos);
        return (NULL);
    }
    if (pos != -1) {
        if (pos < 0) {
            fprintf(stderr, "%d: Event not found\n", pos);
            return (NULL);
        }
        return (my_strdup(((histo_cmd_t *)histo->elements[pos])->cmd));
    }
    else {
        ret = get_cmd_from_str(histo, cmd);
        if (!ret)
            fprintf(stderr, "%s: Event not found\n", cmd);
        return (ret);
    }
}

char *get_cmd_histo(vector_t *histo, char *cmd)
{
    int pos = -1;

    if (*cmd++ != '!')
        return (NULL);
    if (*cmd == '!')
        pos = histo->size - 1;
    if (*cmd == '-' && !is_all_number(cmd + 1)) {
        pos = histo->size - atoi(cmd + 1);
        if (pos < 0 || pos > (int)histo->size) {
            fprintf(stderr, "%d: Event not found\n", pos);
            return (NULL);
        }
    }
    if (*cmd == '#') {
        printf("\n");
        return (cmd = my_strdup(""));
    }
    if (!is_all_number(cmd))
        pos = atoi(cmd) - 1;
    return (get_cmd_histo_two(histo, cmd, pos));
}