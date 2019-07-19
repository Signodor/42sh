/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** repeat
*/

#include "vector.h"
#include "errors.h"
#include "builtins.h"
#include "utils.h"
#include "command.h"
#include "str.h"
#include "shell.h"
#include "alias.h"
#include <string.h>

int check_errors(char **argv)
{
    char *buf;
    int nb = 0;

    if (!argv[1] || !argv[2])
        return (error_param_int("repeat", "Too few arguments."));
    nb = strtoll(argv[1], &buf, 10);
    if (!buf || *buf != '\0')
        return (error_param_int("repeat", "Badly formed number."));
    return (nb < 0 ? 0 : nb);
}

int repeat(char **argv, vector_t *env)
{
    shell_t *shell = get_shell();
    int nb = 0;
    char *cmd = NULL;

    if ((nb = check_errors(argv)) <= 0)
        return (nb);
    for (int i = 2; argv[i]; i++)
        cmd = my_strcat(my_strcat(my_strdup(cmd), " "), argv[i]);
    for (long long int i = 0; i < nb; i++) {
        parse(shell->waiting, cmd, false);
        launch(shell->waiting->elements[shell->waiting->size - 1]);
        command_destroy(shell->waiting->elements[shell->waiting->size - 1]);
        vector_pop_at(shell->waiting, shell->waiting->size - 1);
    }
    if (cmd)
        my_free(cmd);
    return (0);
}