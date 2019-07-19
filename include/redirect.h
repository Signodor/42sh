/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** redirect
*/

#ifndef REDIRECT_H_
#define REDIRECT_H_

#include <stdbool.h>
#include "typedefs.h"

enum redir_e
{
    R_STANDARD,
    R_FILE,
    R_PIPE,
};

struct redirect
{
    redir_t type;

    bool append;
    char *filepath;

    command_t *dir;

    int fd;
};

#endif /* !REDIRECT_H_ */
