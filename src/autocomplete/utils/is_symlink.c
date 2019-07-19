/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_symlink
*/

#include "auto_complete_sys.h"

int is_symlink(char *name, char *folder, char type)
{
    struct stat fd;
    char *folder_temp = my_strdup(folder);
    char *path = my_strcat(folder_temp, name);

    if (!path) {
        if (folder_temp)
            free(folder_temp);
        return (0);
    }
    if (lstat(path, &fd) < 0) {
        free(path);
        return (0);
    }
    free(path);
    if (S_ISLNK(fd.st_mode) == 1)
        return (1);
    return (0);
}