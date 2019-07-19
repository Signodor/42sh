/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** command
*/

#ifndef COMMAND_H_
#define COMMAND_H_

#include <stdlib.h>
#include "typedefs.h"
#include "redirect.h"
#include "vector.h"

struct command
{
    __pid_t pid;

    size_t nb_args;
    char *binary;
    char **arguments;

    redirect_t in;
    redirect_t out;

    command_t *fail;
    command_t *success;
};

command_t *command_parse(char **);
int get_arguments(command_t *command, char **);
void command_destroy(command_t *);
int parse(vector_t *waiting, char *line, bool add_histo);


/*
** redirections.c
*/

int redirect_in(redirect_t *redir, command_t *command);
int redirect_out(redirect_t *redir, command_t *command);


/*
** pipes.c
*/

int create_pipe(command_t *src, command_t *dst);
void add_pipefd(int fd);
void close_fds(void);
void clean_fds(void);


/*
** signals
*/

void signal_handler(void);
int handle_exec_status(int status);
int check_command(char *path);


/*
** exec.c
*/

int launch(command_t *first);


/*
** parse_arg.c
*/

int parse_arg(vector_t *args, char *arg, command_t *command);


/*
** line.c
*/

char *get_line_res(vector_t *vec);
char **parse_line(char *line, bool add_histo);


/*
** globbings.c
*/

int glob_arg(command_t *command, vector_t *args, char *arg);
bool is_globable(vector_t *args, char *arg);


/*
** magic.c
*/

int magic(vector_t *args, char *arg, command_t *command);
char *get_magic_res(char *com);

#endif /* !COMMAND_H_ */
