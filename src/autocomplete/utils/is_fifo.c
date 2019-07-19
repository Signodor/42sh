/*
** EPITECH PROJECT, 2019
** PSU_my_autocomplete
** File description:
** is_fifo
*/

#include "auto_complete_sys.h"

int is_fifo(char *name, char *folder, char type)
{
    char *folder_temp = my_strdup(folder);
    char *path = my_strcat(folder_temp, name);
    struct stat buff;

    if (!path) {
        if (folder_temp)
            free(folder_temp);
        return (0);
    } else if (lstat(path, &buff) < 0) {
        free(path);
        return (0);
    }
    free(path);
    if (buff.st_mode & S_IFIFO)
        return (1);
    return (0);
}