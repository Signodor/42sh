/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** pipes
*/

#include <string.h>
#include <stdio.h>
#include "command.h"
#include "control.h"
#include "str.h"
#include "errors.h"

int create_pipe(command_t *src, command_t *dst)
{
    int fd[2];

    if (pipe(fd) == -1) {
        command_destroy(dst);
        src->out.dir = NULL;
        src->out.fd = 1;
        return (0);
    }
    src->out.fd = fd[1];
    add_pipefd(fd[1]);
    dst->in.fd = fd[0];
    add_pipefd(fd[0]);
    return (0);
}

int con_pipe(command_t *command, char **content)
{
    if (command->out.type != R_STANDARD)
        return (error_int(ALREADY_REDIR));
    if (!command->nb_args)
        return (error_int(NULL_COMMAND));
    command->out.type = R_PIPE;
    command->out.dir = command_parse(content);
    if (!command->out.dir)
        return (-1);
    if (command->out.dir->in.type != R_STANDARD) {
        command_destroy(command->out.dir);
        return (error_int(ALREADY_REDIR));
    }
    command->out.dir->in.dir = command;
    command->out.dir->in.type = R_PIPE;
    return (0);
}