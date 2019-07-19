/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_folder
*/

#include "auto_complete_sys.h"

char *get_root_path(char *str)
{
    size_t size = 0;
    char *bin = NULL;
    char *res = NULL;

    if (str && str[0] == '/')
        return (NULL);
    res = getcwd(bin, size);
    if (res && res[0] && (!str || str[0] != '/'))
        res = my_strcat(res, "/");
    return (res);
}

char *get_current_path(char *str, auto_complete_t *content)
{
    char *res = NULL;

    if (!str || !str[0] || !(res = my_strdup(str)))
        return (NULL);
    for (int i = strlen(res); i >= 0; i--) {
        if (res[i] == '/') {
            res[i + 1] = 0;
            break;
        } else if (i == 0) {
            free(res);
            res = NULL;
        }
    }
    return (res);
}

char *get_folder(char *str, auto_complete_t *content)
{
    char *res = get_root_path(str);
    char *temp = get_current_path(str, content);

    if (!str)
        return (res);
    res = my_strcat(res, temp);
    free(temp);
    return (res);
}