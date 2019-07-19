/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** deconstruct
*/

#include <stdlib.h>
#include "shell.h"
#include "utils.h"
#include "env.h"
#include "str.h"
#include "history.h"

shell_t *shell_init(char *envp[])
{
    shell_t *shell = my_malloc(sizeof(shell_t));

    if (!(shell->aliases = vector_create()))
        my_exit(84);
    if (!(shell->env = env_create(envp)))
        my_exit(84);
    if (!get_env(shell->env, "PWD"))
        set_env(shell->env, my_strdup("PWD"), getcwd(NULL, 0));
    if (!get_env(shell->env, "PATH"))
        set_env(shell->env, my_strdup("PATH"),
        my_strdup("/bin:/usr/local/bin:/sbin:/usr/bin:/usr/sbin"));
    shell->commands = vector_create();
    shell->local_var = vector_create();
    shell->history = vector_create();
    shell->histo_up = true;
    shell->ignoreeof = 1;
    shell_single(shell);
    return (shell);
}

shell_t *shell_single(shell_t *shell)
{
    static shell_t *sh = NULL;

    if (shell)
        sh = shell;
    return (sh);
}

shell_t *get_shell(void)
{
    return (shell_single(NULL));
}

void shell_destroy(shell_t *shell)
{
    if (!shell)
        return;
    env_destroy(shell->env);
    env_destroy(shell->local_var);
    clean_histo(shell->history);
    vector_delete(shell->history);
    vector_delete(shell->aliases);
    pipefds(-1, false);
    vector_delete(shell->commands);
    free(shell);
}