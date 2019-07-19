/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parser
*/

#include <unistd.h>
#include "command.h"
#include "str.h"

static command_t *command_construct(void)
{
    command_t *command;

    if (!(command = malloc(sizeof(command_t))))
        return (NULL);
    command->arguments = NULL;
    command->fail = NULL;
    command->success = NULL;
    command->in.type = R_STANDARD;
    command->in.filepath = NULL;
    command->in.fd = 0;
    command->in.dir = NULL;
    command->out.filepath = NULL;
    command->out.type = R_STANDARD;
    command->out.fd = 0;
    command->out.dir = NULL;
    command->nb_args = 0;
    return (command);
}

command_t *command_parse(char **content)
{
    command_t *command = command_construct();

    if (!command)
        return (NULL);
    if (get_arguments(command, content)) {
        command_destroy(command);
        return (NULL);
    }
    return (command);
}

int parse(vector_t *waiting, char *line, bool add_histo)
{
    command_t *command;
    char **tab = parse_line(line, add_histo);
    char *str;

    if (!tab)
        return (-1);
    for (size_t i = 0; tab[i]; i++) {
        str = tab[i];
        if (empty_line(str))
            continue;
        if ((command = command_parse(&str)))
            vector_append(waiting, command);
    }
    free_str_tab(tab);
    return (0);
}