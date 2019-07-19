/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** foreach
*/

#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "errors.h"
#include "builtins.h"
#include "utils.h"
#include "command.h"
#include "str.h"
#include "shell.h"
#include "alias.h"
#include "get_next_line.h"
#include "history.h"

vector_t *get_cmds(shell_t *shell);

char *get_cmd_parsed(char *line)
{
    command_t *command;
    char **tab = parse_line(line, true);
    char *str;
    char *ret = NULL;

    if (!tab)
        return (NULL);
    for (size_t i = 0; tab[i]; i++) {
        str = tab[i];
        if (empty_line(str) || !(command = command_parse(&str)))
            continue;
        for (unsigned int j = 0; j < command->nb_args; j++)
            ret = my_strcat(my_strdup(ret), my_strcat(my_strdup(" "),
            command->arguments[j]));
        if (tab[i + 1])
            ret = my_strcat(my_strdup(ret), " ; ");
    }
    free_str_tab(tab);
    command_destroy(command);
    return (ret);
}

int foreach_in(shell_t *shell, vector_t *ret, char *str)
{
    vector_t *cmds = NULL;
    char **argv = str_to_tab(str, " ");
    static int sex = 0;

    if (!argv[0] || !argv[1])
        return (error_param_int("foreach", "Too few arguments."));
    if (!(cmds = get_cmds(shell)))
        return (error_param_int("foreach", "end not found."));
    for (int i = 2; argv[i]; i++) {
        if (!strcmp(argv[i], "(") || !strcmp(argv[i], ")"))
            continue;
        set_env(shell->local_var, my_strdup(argv[1]), my_strdup(argv[i]));
        for (int j = 0; cmds->elements[j]; j++)
            vector_append(ret, get_cmd_parsed(cmds->elements[j]));
    }
    while (cmds->size)
        vector_pop(cmds);
    mode(1);
    return (0);
}

vector_t *get_cmds(shell_t *shell)
{
    vector_t *ret = vector_create();
    char *line = NULL;

    mode(1);
    do {
        fprintf(stderr, "foreach? ");
        line = get_next_line(0);
        if (!line) {
            mode(0);
            return (NULL);
        } if (!strcmp(line, "end"))
            break;
        if (!strncmp(line, "foreach", 7))
            foreach_in(shell, ret, get_cmd_parsed(line));
        else {
            vector_append(ret, line);
            add_histo(line, shell->history);
        }
    } while (strcmp(line, "end"));
    mode(0);
    return (ret);
}

int foreach(char **argv, vector_t *env)
{
    vector_t *cmds = NULL;
    shell_t *shell = get_shell();

    if (!argv[0] || !argv[1])
        return (error_param_int("foreach", "Too few arguments."));
    if (!(cmds = get_cmds(shell)))
        return (error_param_int("foreach", "end not found."));
    for (int i = 2; argv[i]; i++) {
        if (!strcmp(argv[i], "(") || !strcmp(argv[i], ")"))
            continue;
        set_env(shell->local_var, my_strdup(argv[1]), my_strdup(argv[i]));
        for (unsigned int j = 0; j < cmds->size; j++) {
            parse(shell->waiting, cmds->elements[j], false);
        }
    }
    while (cmds->size)
        vector_pop(cmds);
    return (0);
}