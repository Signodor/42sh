/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** get_path
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "vector.h"
#include "str.h"
#include "utils.h"
#include "env.h"

size_t get_size(char *path)
{
    size_t size = 1;

    if (!path)
        return (0);
    for (int i = 0; path[i]; i++)
        if (path[i] == ':')
            size++;
    return (size);
}

char **get_paths(void)
{
    shell_t *shell = get_shell();
    char *path = get_env(shell->env, "PATH");
    char **pathes;
    size_t size = get_size(path);

    if (!path)
        return (NULL);
    pathes = my_malloc(sizeof(char *) * (size + 1));
    for (size_t i = 0; i < size; i++) {
        pathes[i] = my_strdup_toch(path, ':');
        path += strlen(pathes[i]) + 1;
    }
    pathes[size] = NULL;
    return (pathes);
}