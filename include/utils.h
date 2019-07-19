/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** utils
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <unistd.h>
#include <stdbool.h>
#include "typedefs.h"
#include "vector.h"

/*
** check_malloc_free.c
*/

void *my_malloc(size_t size);
void my_free(void *ptr);
void check_ptr(void const *ptr);


/*
** pipes.c
*/

vector_t *pipefds(int fd, bool up);
void clean_fds(void);
void close_fds(void);
void add_pipefd(int fd);


/*
** binary.c
*/

char **get_paths(void);
int get_binary(command_t *command, char *arg);
char *founded(char *path, char *arg);
int verifill(command_t *command);

/*
** ioctl.c
*/

void mode(int which);
unsigned short get_row(void);
unsigned short get_col(void);


/*
** my_exit.c
*/

void my_exit(int code);

int create_tmp_file(void);

#endif /* !UTILS_H_ */
