/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_result
*/

#include "auto_complete_sys.h"

int get_nb_cummun_chr(char *str1, char *str2)
{
    int res = 0;

    for (int i = 0; str1[i] && str2[i]; i++) {
        if (str1[i] == str2[i])
            res++;
        else
            break;
    }
    return (res);
}

int max_cummun_chr_current(char *current, int size_max,
auto_complete_t *content)
{
    content_t *temp = NULL;
    int size_temp = 0;
    char *current_file = clean_current_path(current);

    if (!current_file)
        return (size_max);
    for (temp = content->content; temp; temp = temp->next) {
        size_temp = get_nb_cummun_chr(temp->name, current_file);
        size_max = (size_max > size_temp) ? size_temp : size_max;
    }
    return (size_max);
}

int get_max_cummun_chr(auto_complete_t *content, char *current_file)
{
    content_t *loop = content->content;
    content_t *temp = NULL;
    int size_max = 1000;
    int size_temp = 0;

    if (content_size(content) == 1)
        size_max = strlen(content->content->name);
    while (loop) {
        temp = loop->next;
        while (temp) {
            size_temp = get_nb_cummun_chr(loop->name, temp->name);
            size_max = (size_max > size_temp) ? size_temp : size_max;
            temp = temp->next;
        }
        loop = loop->next;
    }
    return (size_max);
}

char *get_max_file(auto_complete_t *content, int size)
{
    if (content_size(content) == 1 && (size_t)size ==
    strlen(content->content->name) && content->content->type == '/')
        return (my_strcat(my_strdup(content->content->name), "/"));
    return (my_strndup(content->content->name, size));
}

char *auto_complete_set_result(auto_complete_t *content, char *current,
char *current_file)
{
    char *max_file = NULL;
    char *folder = get_current_path(current, content);
    char *res = NULL;
    int size = get_max_cummun_chr(content, current_file);

    if (content->content) {
        max_file = get_max_file(content, size);
        if (folder)
            res = my_strcat(my_strdup(folder), max_file);
        else
            res = my_strdup(max_file);
        res = end_space(content, res);
        free(max_file);
    }
    free(folder);
    return (res);
}