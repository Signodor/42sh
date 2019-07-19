/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_folder
*/

#include "auto_complete_sys.h"

int is_folder(char *str, char type)
{
    if (type == '/')
        return (1);
    for (int i = 0; str[i]; i++)
        if (str[i] == '/')
            return (1);
    return (0);
}

int is_folder_type(char *name, char *folder, char type)
{
    if (type == DT_DIR)
        return (1);
    return (0);
}

int is_folder_cmd(char *folder)
{
    char *bin = NULL;
    size_t trash = 0;
    char *path = getcwd(bin, trash);

    if (path && path[strlen(path)] != '/')
        path = my_strcat(path, "/");
    if (folder && path && !strcmp(folder, path)) {
        free(path);
        return (0);
    }
    free(path);
    return (1);
}