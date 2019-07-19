/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** signal_handler
*/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include "shell.h"
#include "command.h"
#include "proto_ncurse.h"
#include "utils.h"

int sig_stats;

static void kill_commands(vector_t *commands, int sig)
{
    command_t *command;

    for (size_t i = 0; i < commands->size; i++) {
        command = (command_t *)commands->elements[i];
        kill(command->pid, sig);
    }
}

static void signal_catcher(int sig)
{
    shell_t *shell = get_shell();
    info_t *info = define_info(false);

    if (sig == SIGINT) {
        if (shell->commands->size)
            kill_commands(shell->commands, SIGINT);
        skip_my_lines(info->first, 1);
        write(1, "\n", 1);
        cursor_pos(display_line(false, 0));
        if (info->first)
            free_letters(info);
    }
}

void signal_handler(void)
{
    if (signal(SIGINT, signal_catcher) == SIG_ERR) {
        fprintf(stderr, "Error on signal handler\n");
        my_exit(84);
    }
}