/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_executable
*/

#include "auto_complete_sys.h"

int is_executable(char *name, char *folder, char type)
{
    struct stat fd;
    char *folder_temp = my_strdup(folder);
    char *path = my_strcat(folder_temp, name);

    if (!path) {
        if (folder_temp)
            free(folder_temp);
        return (0);
    }
    stat(path, &fd);
    free(path);
    if (fd.st_mode & S_IXUSR || fd.st_mode & S_IXGRP || fd.st_mode & S_IXOTH)
        return (1);
    return (0);
}