/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** check_malloc_free
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "errors.h"
#include "utils.h"

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr) {
        error_msg(NAME, MALLOC_FAILED);
        my_exit(84);
    }
    return (ptr);
}

void my_free(void *ptr)
{
    if (!ptr) {
        write(2, "Cannot free", 11);
        my_exit(84);
    }
    free(ptr);
}

void check_ptr(void const *ptr)
{
    if (!ptr) {
        error_msg(NAME, "Error: NULL pointer");
        my_exit(84);
    }
}