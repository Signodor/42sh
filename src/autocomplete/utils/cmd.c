/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_cmd
*/

#include "auto_complete_sys.h"
char *clean_line(char *line);

int auto_complete_is_cmd(char *cmd_raw)
{
    int i = 0;
    char *cmd = clean_line(cmd_raw);

    if (!cmd || !cmd[0])
        return (1);
    for (i = strlen(cmd); i >= 0 && cmd[i] != ' ' && cmd[i] != ';' &&
    cmd[i] != '|' && cmd[i] != '&' && cmd[i] != '>' && cmd[i] != '<'; i--);
    for (; i >= 0 && cmd[i] == ' '&& cmd[i] != ';' &&
    cmd[i] != '|' && cmd[i] != '&' && cmd[i] != '>' && cmd[i] != '<'; i--);
    if (i < 0 || cmd[i] == ';' || cmd[i] == '|' || cmd[i] == '&')
        return (1);
    return (0);
}

char *auto_complete_tild(char *cmd)
{
    shell_t *shell = get_shell();
    char *home = get_env(shell->env, "HOME");
    char *res = NULL;

    if (home) {
        home = my_strdup(home);
        if (home[strlen(home)] != '/')
            home = strcat(home, "/");
    }
    for (int i = 0; i < 2; i++)
        mv_left_arr(cmd);
    res = my_strcat(home, cmd);
    free(cmd);
    return (res);
}

char *clean_full_cmd(char *cmd, int change_tilt)
{
    char *res = NULL;
    int i = 0;

    if (!cmd || !cmd[0] || !(res = my_strdup(cmd)))
        return (NULL);
    for (i = strlen(res); i >= 0 && res[i] != ' ' && res[i] != ';' &&
    res[i] != '|' && res[i] != '&' && res[i] != '>' && res[i] != '<'; i--);
    i++;
    for (int j = 0; j < i; j++)
        mv_left_arr(res);
    if (change_tilt && res[0] == '~' && res[1] == '/')
        res = auto_complete_tild(res);
    return (res);
}

char *get_beg_cmd(char *cmd)
{
    char *res = NULL;
    int i = 0;

    if (!cmd || !cmd[0] || !(res = my_strdup(cmd)))
        return (NULL);
    for (i = strlen(res); i >= 0 && res[i] != ' ' && res[i] != ';' &&
    res[i] != '|' && res[i] != '&' && res[i] != '>' && res[i] != '<'; i--);
    if (i < 0) {
        free(res);
        return (NULL);
    }
    else if (res[i + 1] == 0)
        return (res);
    res[i + 1] = 0;
    return (res);
}