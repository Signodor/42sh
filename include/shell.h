/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** global
*/

#ifndef SHELL_H_
#define SHELL_H_

#include <stdbool.h>
#include "typedefs.h"
#include "vector.h"

struct shell
{
    vector_t *commands;

    vector_t *env;
    vector_t *local_var;
    vector_t *aliases;
    vector_t *history;
    vector_t *waiting;

    bool histo_up;
    int ignoreeof;
};

/*
** deconstruct.c
*/

shell_t *shell_init(char *envp[]);
shell_t *shell_single(shell_t *shell);
shell_t *get_shell(void);
void shell_destroy(shell_t *shell);
void signal_handler(void);

/*
** line.c
*/

size_t display_line(bool update, int new);

int main_loop(void);
#endif /* !SHELL_H_ */
