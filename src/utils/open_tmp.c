/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** open_tmp
*/

#include <fcntl.h>
#include <stdio.h>

int create_tmp_file(void)
{
    FILE *file = tmpfile();
    int fd;

    if (!file)
        return (-1);
    fd = fileno(file);
    return (fd);
}