/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** status
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

int handle_exec_status(int status)
{
    if (status == 13)
        return (-1);
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == 8)
            fprintf(stderr, "Floating exception");
        else
            fprintf(stderr, "%s", strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
            fprintf(stderr, " (core dumped)");
        fprintf(stderr, "\n");
        return (-1);
    }
    return (0);
}
