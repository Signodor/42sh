/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_path
*/

#include "auto_complete_sys.h"

char *my_strdup_to_ch(char *str, char end)
{
    char *ret;
    size_t size;

    for (size = 0; str[size] && str[size] != end; size++);
    ret = malloc(sizeof(char) * (size + 1));
    if (!ret)
        return (NULL);
    for (size_t i = 0; i < size; i++)
        ret[i] = str[i];
    ret[size] = 0;
    return (ret);
}

vector_t *create_vector_path(char *path)
{
    vector_t *res = vector_create();
    int size = 1;

    if (!path) {
        if (res)
            vector_delete(res);
        return (NULL);
    }
    for (int i = 0; path[i]; i++)
        size += path[i] == ':';
    for (int i = 0; i < size; i++) {
        vector_append(res, my_strdup_to_ch(path, ':'));
        path += strlen(res->elements[i]) + 1;
    }
    return (res);
}

void remove_path_name(char *path)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; path[j]; j++)
            path[j] = path[j + 1];
}

vector_t *auto_complete_get_path(vector_t *env)
{
    char *path = NULL;
    vector_t *res = NULL;

    path = get_env(env, "PATH");
    if (path)
        path = my_strdup(path);
    res = create_vector_path(path);
    free(path);
    return (res);
}