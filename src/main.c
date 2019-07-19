/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** main
*/

#include <stdio.h>
#include "shell.h"
#include "env.h"
#include "history.h"
#include "utils.h"
#include "get_next_line.h"
#include "proto_ncurse.h"

int main(int argc, char **argv, char *envp[])
{
    shell_t *shell = shell_init(envp);

    setbuf(stdout, NULL);
    signal_handler();
    mode(0);
    special_variables();
    main_loop();
    mode(1);
    shell_destroy(shell);
    free(char_realloc(NULL, 1));
    define_info(true);
    write(1, "exit\n", 5);
    return (0);
}