/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** redirections
*/

#include <string.h>
#include "command.h"
#include "control.h"
#include "str.h"
#include "errors.h"

static int main_redir(redirect_t *redir, bool append, char **content)
{
    int status = 0;
    char *file = get_arg(content, &status);

    if (status || !file || is_control(file))
        return (error_int(NO_REDIR_NAME));
    if (redir->type != R_STANDARD)
        return (error_int(ALREADY_REDIR));
    redir->type = R_FILE;
    redir->filepath = file;
    redir->append = append;
    return (0);
}

int con_right(command_t *command, char **content)
{
    return (main_redir(&command->out, false, content));
}

int con_double_right(command_t *command, char **content)
{
    return (main_redir(&command->out, true, content));
}

int con_left(command_t *command, char **content)
{
    return (main_redir(&command->in, false, content));
}

int con_double_left(command_t *command, char **content)
{
    return (main_redir(&command->in, true, content));
}