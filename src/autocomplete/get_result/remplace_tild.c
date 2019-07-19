/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** remplace_tild
*/

#include "auto_complete_sys.h"

void mv_left_arr_from(char *str, int from)
{
    if (!str || strlen(str) <= (size_t)from)
        return;
    for (; str[from]; from++)
        str[from] = str[from + 1];
}

void auto_complete_remplace_tild(char *current_cmd, char *res)
{
    shell_t *shell = get_shell();
    char *home = get_env(shell->env, "HOME");
    int i = 0;
    int home_size = 0;

    if (!home)
        return;
    if (home)
        home_size = strlen(home);
    for (int i = 0; current_cmd[i] && current_cmd[i] != '~'; i++);
    if (!current_cmd[i])
        return;
    for (int j = 0; j < home_size - 1; j++)
        mv_left_arr_from(res, i);
    res[i] = '~';
}
