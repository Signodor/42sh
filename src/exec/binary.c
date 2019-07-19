/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** binary
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <stdbool.h>
#include <string.h>
#include "errors.h"
#include "utils.h"
#include "command.h"
#include "builtins.h"
#include "str.h"

int check_command(char *path)
{
    struct stat binary;

    if (stat(path, &binary) == -1)
        return (error_param_int(path, COMMAND_NOT_FOUND));
    if (!S_ISREG(binary.st_mode) || access(path, X_OK))
        return (error_param_int(path, PERMISSION_DENIED));
    return (0);
}

char *founded(char *path, char *arg)
{
    char *binary = malloc(sizeof(char) * (strlen(path) + strlen(arg) + 2));

    strcpy(binary, path);
    binary[strlen(path)] = '/';
    strcpy(binary + strlen(path) + 1, arg);
    if (access(binary, X_OK)) {
        free(binary);
        return (NULL);
    }
    return (binary);
}

int get_binary(command_t *command, char *arg)
{
    char **pathes;

    command->binary = NULL;
    if (my_strcontain(arg, "/")) {
        command->binary = my_strdup(arg);
        return (0);
    }
    if (!(pathes = get_paths()))
        return (error_param_int(arg, COMMAND_NOT_FOUND));
    for (size_t i = 0; pathes[i]; i++) {
        if (!command->binary)
            command->binary = founded(pathes[i], arg);
        free(pathes[i]);
    }
    free(pathes);
    if (!command->binary)
        return (error_param_int(command->arguments[0], COMMAND_NOT_FOUND));
    return (0);
}

int verifill(command_t *command)
{
    char **pathes = NULL;
    bool found = false;

    if (is_builtin(command->arguments[0]))
        return (0);
    if (get_binary(command, command->arguments[0]))
        return (-1);
    return (check_command(command->binary));
}