/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history
*/

#include "vector.h"
#include "str.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "history.h"
#include "shell.h"
#include "command.h"

int is_all_number(char *str);

char *add_args(char *ret, char *str)
{
    for (int i = 1; str[i]; i++) {
        if (str[i] == 'c')
            ret[ARG_C] = 1;
        if (str[i] == 'h')
            ret[ARG_H] = 1;
        if (str[i] == 'r')
            ret[ARG_R] = 1;
        if (str[i] != 'c' && str[i] != 'h' && str[i] != 'r') {
            fprintf(stderr, "Usage: history [-chr] [# number of events].\n");
            return (NULL);
        }
    }
    return (ret);
}

char *get_args_histo(char **argv)
{
    char *ret = (char *)calloc(4, sizeof(char));

    for (int i = 1; argv[i]; i++) {
        if (!is_all_number(argv[i]))
            ret[ARG_NB] = atoi(argv[i]);
        else if (*argv[i] == '-')
            ret = add_args(ret, argv[i]);
        else {
            fprintf(stderr, "Usage: history [-chr] [# number of events].\n");
            return (NULL);
        }
    }
    return (ret);
}

int history_cmd(char *args, shell_t *shell)
{
    if (!args)
        return (1);
    if (args[ARG_C])
        clean_histo(shell->history);
    else
        print_histo(shell->history, args);
    return (0);
}

int handle_history(char **argv, vector_t *env)
{
    char *cmd = my_strdup(argv[0]);
    shell_t *shell = get_shell();
    char *args;

    for (int i = 1; argv[i]; i++)
        cmd = my_strcat(my_strcat(my_strdup(cmd), " "), argv[i]);
    if (!strcmp(argv[0], "history")) {
        args = get_args_histo(argv);
        return (history_cmd(args, shell));
    }
    cmd = get_cmd_histo(shell->history, cmd);
    if (cmd && strcmp(cmd, "")) {
        parse(shell->waiting, cmd, true);
        return (0);
    }
    if (cmd && !strcmp(cmd, ""))
        return (0);
    return (-1);
}