/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** control
*/

#ifndef CONTROL_H_
#define CONTROL_H_

#include "typedefs.h"

struct control
{
    char const *name;
    int (*call)(command_t *, char **);
};

int call(command_t *command, char **content, char *str);


/*
** redirections.c
*/

int con_right(command_t *command, char **content);
int con_double_right(command_t *command, char **content);
int con_left(command_t *command, char **content);
int con_double_left(command_t *command, char **content);


/*
** pipes.c
*/

int con_pipe(command_t *command, char **content);


/*
** conditionnals.c
*/

int con_fail(command_t *command, char **content);
int con_success(command_t *command, char **content);

#endif /* !CONTROL_H_ */
