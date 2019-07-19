/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 
*/

#ifndef BUILTINS_H_
#define BUILTINS_H_

#include <stdbool.h>
#include "vector.h"
#include "env.h"
#include "typedefs.h"
#include "linked.h"

struct builtins_models
{
    char *name;
    int (*builtin)(char **, vector_t *);
};

/*
** verify.c
*/

bool is_builtin(char *name);

/*
** builtins.c
*/

int builtins(command_t *, char **argv, vector_t *env);
int c_setenv(char **argv, vector_t *env);
int c_unsetenv(char **argv, vector_t *env);
int display_env(char **argv, vector_t *env);
int my_cd(char **argv, vector_t *env);
int handle_history(char **argv, vector_t *env);
int c_echo(char **argv, vector_t *env);
int repeat(char **argv, vector_t *env);
int foreach(char **argv, vector_t *env);

/*
** where.c
*/

int where(char **argv, vector_t *env);
int which(char **argv, vector_t *env);


/*
** local.c
*/

int local(char **argv, vector_t *env);
int unset(char **argv, vector_t *env);

#endif /* !BUILTINS_H_ */
