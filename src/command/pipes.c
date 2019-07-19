/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** pipes
*/

#include <stdbool.h>
#include <stdio.h>
#include "vector.h"
#include "utils.h"

vector_t *pipefds(int fd, bool up)
{
    static vector_t *vector = NULL;

    if (!vector)
        if (!(vector = vector_create()))
            my_exit(84);
    if (up)
        vector_append(vector, (void *)(long long)fd);
    else if (fd == -1 && vector) {
        vector_delete(vector);
        vector = NULL;
    }
    return (vector);
}

void add_pipefd(int fd)
{
    pipefds(fd, true);
}

void close_fds(void)
{
    vector_t *fds = pipefds(0, false);

    if (!fds)
        return;
    for (size_t i = 0; i < fds->size; i++) {
        close((int)(long long)fds->elements[i]);
    }
}

void clean_fds(void)
{
    vector_t *fds = pipefds(0, false);

    if (!fds)
        return;
    while (fds->size)
        vector_pop(fds);
}