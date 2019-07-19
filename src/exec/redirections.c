/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** redirections
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "command.h"
#include "get_next_line.h"
#include "utils.h"

static int redirect_tmp(redirect_t *redir)
{
    int fd = create_tmp_file();
    char *line;

    if (fd == -1)
        return (-1);
    mode(1);
    printf("> ");
    while ((line = get_next_line(0))) {
        if (!strcmp(line, redir->filepath))
            break;
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
        printf("> ");
    }
    mode(0);
    lseek(fd, 0, SEEK_SET);
    return (fd);
}

int redirect_in_file(redirect_t *redir)
{
    int fd;

    if (redir->append)
        fd = redirect_tmp(redir);
    else
        fd = open(redir->filepath, O_RDONLY);
    if (fd == -1) {
        write(2, redir->filepath, strlen(redir->filepath));
        if (errno == 1)
            write(2, ": Permission denied.\n", 21);
        else
            write(2, ": No such file or directory.\n", 29);
        return (-1);
    }
    redir->fd = fd;
    return (0);
}

int redirect_in(redirect_t *redir, command_t *command)
{
    if (redir->type == R_STANDARD)
        return (0);
    if (redir->type == R_FILE)
        if (redirect_in_file(redir) == -1)
            return (-1);
    dup2(command->in.fd, 0);
    return (0);
}

int redirect_out_file(redirect_t *redir)
{
    int flags = O_CREAT | O_WRONLY;
    int fd;

    if (redir->append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    if ((fd = open(redir->filepath, flags, 0644)) == -1) {
        write(2, redir->filepath, strlen(redir->filepath));
        write(2, ": Permission denied.\n", 21);
        return (-1);
    }
    redir->fd = fd;
    return (0);
}

int redirect_out(redirect_t *redir, command_t *command)
{
    if (redir->type == R_STANDARD)
        return (0);
    if (redir->type == R_FILE)
        if (redirect_out_file(redir) == -1)
            return (-1);
    dup2(command->out.fd, 1);
    return (0);
}