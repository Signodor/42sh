/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** lopp
*/

#include <stdbool.h>
#include "command.h"
#include "vector.h"
#include "shell.h"
#include "utils.h"
#include "proto_ncurse.h"
#include "get_next_line.h"
#include "str.h"
#include "env.h"

char *get_line(void)
{
    static int tty = -1;

    if (tty == -1)
        tty = isatty(STDIN_FILENO);
    if (tty)
        return (prototype_ncurse());
    return (get_next_line(STDIN_FILENO));
}

int main_loop(void)
{
    shell_t *shell = get_shell();
    shell->waiting = vector_create();
    char *line = NULL;
    int status = 0;

    while (cursor_pos(display_line(true, status)) && (line = get_line())) {
        clean_fds();
        status = 0;
        if ((status = parse(shell->waiting, line, true)))
            continue;
        while (shell->waiting->size) {
            status = launch(shell->waiting->elements[0]);
            command_destroy(shell->waiting->elements[0]);
            vector_pop_at(shell->waiting, 0);
        }
        verif_specials_variables();
        free(line);
        mode(0);
    }
    vector_delete(shell->waiting);
    return (0);
}