/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include <string.h>
#include <stdio.h>
#include "str.h"
#include "shell.h"
#include "utils.h"
#include "linked.h"
#include "alias.h"

void add_alias(vector_t *aliases, char **argv)
{
    alias_t *alias = my_malloc(sizeof(alias_t));
    alias_t *old = NULL;
    char *arg;
    char *line;
    int status = 0;

    alias->name = my_strdup(argv[1]);
    alias->cmd = NULL;
    for (size_t i = 2; argv[i] && !status; i++) {
        line = argv[i];
        while ((arg = get_arg(&line, &status)) && !status)
            alias->cmd = linked_append(alias->cmd, arg);
    }
    unalias_this(aliases, get_alias_name(aliases, argv[1]));
    vector_append(aliases, alias);
}

int alias(char **argv, vector_t *env)
{
    shell_t *shell = get_shell();
    vector_t *aliases = shell->aliases;
    alias_t *alias = NULL;

    if (!argv[1]) {
        print_all_alias(aliases);
    } else if (argv[1] && !argv[2]) {
        print_spe_alias(aliases, argv[1]);
    } else
        add_alias(aliases, argv);
    return (0);
}

void unalias_this(vector_t *aliases, alias_t *alias)
{
    if (!alias)
        return;
    free(alias->name);
    linked_free(alias->cmd);
    free(alias);
    vector_pop_this(aliases, alias);
}

int unalias(char **argv, vector_t *env)
{
    shell_t *shell = get_shell();
    alias_t *alias = NULL;
    int res = 0;

    if (argv[1] == NULL) {
        fprintf(stderr, "unalias: Too few arguments.\n");
        return (0);
    }
    for (size_t i = 1; argv[i]; i++)
        unalias_this(shell->aliases, get_alias_name(shell->aliases, argv[i]));
    return (0);
}