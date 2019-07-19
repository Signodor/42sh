/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exec
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "command.h"
#include "env.h"
#include "builtins.h"
#include "shell.h"
#include "utils.h"
#include "str.h"
#include "errors.h"

void exec(command_t *command, char *argv[], char *envp[], vector_t *env)
{
    char *buf = NULL;
    size_t size = 0;

    if (redirect_in(&command->in, command) == -1)
        my_exit(1);
    if (redirect_out(&command->out, command) == -1)
        my_exit(1);
    close_fds();
    if (verifill(command) == -1)
        my_exit(1);
    if (is_builtin(command->arguments[0]))
        my_exit(builtins(command, argv, env));
    execve(command->binary, argv, envp);
    write(2, argv[0], strlen(argv[0]));
    write(2, ": Exec format error. Wrong Architecture.\n", 41);
}

int command_exec(command_t *command, shell_t *shell)
{
    char **envp;

    if (is_builtin(command->arguments[0]) && command->out.type != R_PIPE)
        return (builtins(command, command->arguments, shell->env));
    if (command->out.type == R_PIPE && command->out.dir)
        if (create_pipe(command, command->out.dir))
            return (-1);
    envp = get_envp(shell->env);
    if ((command->pid = fork()) == -1)
        return (-1);
    if (!command->pid)
        exec(command, command->arguments, envp, shell->env);
    vector_append(shell->commands, command);
    if (command->out.type == R_PIPE && command->out.dir)
        return (command_exec(command->out.dir, shell));
    for (size_t i = 0; envp[i]; i++)
        free(envp[i]);
    free(envp);
    return (0);
}

void skip(command_t *command, int status)
{
    if (command->out.type == R_PIPE && command->out.dir)
        return (skip(command->out.dir, status));
    if (command->success && status)
        return (skip(command->success, status));
    if (!status && command->success)
        launch(command->success);
    if (status && command->fail)
        launch(command->fail);
}

int launch(command_t *first)
{
    shell_t *shell = get_shell();
    int status = command_exec(first, shell);
    command_t *command;

    close_fds();
    for (size_t i = 0; i < shell->commands->size && !status; i++) {
        command = (command_t *)shell->commands->elements[i];
        waitpid(command->pid, &status, WUNTRACED);
    }
    handle_exec_status(status);
    skip(first, status);
    while (vector_pop(shell->commands));
    get_shell()->ignoreeof = 1;
    return (status);
}