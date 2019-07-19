/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** precmd
*/

#include <string.h>
#include <stdio.h>
#include "command.h"
#include "str.h"
#include "shell.h"
#include "builtins.h"
#include "utils.h"
#include "alias.h"
#include "linked.h"

static int launch_special(char *line)
{
    vector_t *commands;

    if (!(commands = vector_create()))
        return (-1);

    if (parse(commands, line, true)) {
        vector_delete(commands);
        return (-1);
    }
    while (commands->size) {
        launch(commands->elements[0]);
        command_destroy(commands->elements[0]);
        vector_pop_at(commands, 0);
    }
    vector_delete(commands);
    return (0);
}

void alias_special(char *name)
{
    vector_t *aliases = get_shell()->aliases;
    alias_t *alias = get_alias_name(aliases, name);
    shell_t *shell = get_shell();
    char *line;

    if (!alias)
        return;
    line = linked_concaten(alias->cmd);
    shell->histo_up = false;
    launch_special(line);
    shell->histo_up = true;
    free(line);
}