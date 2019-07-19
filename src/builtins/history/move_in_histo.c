/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** move_in_histo
*/

#include "shell.h"
#include "history.h"
#include <string.h>
#include "str.h"

char *get_old(char *old)
{
    static char *tmp;

    if (old)
        tmp = my_strdup(old);
    else
        return (my_strdup(tmp));
    return (NULL);
}

char *move_in_histo(bool dir, char *old, bool is_new)
{
    shell_t *shell = get_shell();
    static int pos = 0;
    char *ret = old;

    if (!pos || is_new) {
        get_old(old);
        pos = 0;
    } if (!dir && pos <= 1) {
        pos -= pos > 0;
        return (get_old(NULL));
    } if (dir && (int)shell->history->size - pos > 0) {
        ret = my_strdup(((histo_cmd_t *)shell->history->
        elements[shell->history->size - pos - 1])->cmd);
        pos++;
    } if (!dir && pos > 1){
        ret = my_strdup(((histo_cmd_t *)shell->history->
        elements[shell->history->size - pos + 1])->cmd);
        pos--;
    }
    return (ret);
}