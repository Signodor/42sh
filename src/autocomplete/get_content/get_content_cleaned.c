/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_content_cleaned
*/

#include "auto_complete_sys.h"

int clean_points_auto_complete(content_t *temp, auto_complete_t *content,
char *current)
{
    if (!current && temp->name && temp->name[0] == '.') {
        content_pop(temp, content);
        return (1);
    } else if (current && temp->name && temp->name[0] == '.' &&
    current[0] != '.') {
        content_pop(temp, content);
        return (1);
    }
    if (!current)
        return (1);
    return (0);
}

void auto_complete_check_double(auto_complete_t *content, content_t *temp,
content_t *temp2)
{
    if (temp->name && temp2->name && !strcmp(temp->name, temp2->name)
    && temp->type == temp2->type)
        content_pop(temp2, content);
}

void auto_complete_rm_double(auto_complete_t *content)
{
    content_t *temp = content->content;
    content_t *temp2 = NULL;
    content_t *next = NULL;

    while (temp) {
        temp2 = temp->next;
        while (temp2) {
            next = temp2->next;
            auto_complete_check_double(content, temp, temp2);
            temp2 = next;
        }
        temp = temp->next;
    }
}

void clean_content(auto_complete_t *content, char *current, char *full_current,
int is_cmd)
{
    content_t *temp = content->content;
    content_t *next = NULL;

    for (; temp; temp = next) {
        next = temp->next;
        if (clean_points_auto_complete(temp, content, current))
            continue;
        if (temp->name && strncmp(temp->name, current, strlen(current))) {
            content_pop(temp, content);
            continue;
        } else if (is_cmd && temp->type != '/' && temp->type != '*' &&
        temp->type != 'b')
            content_pop(temp, content);
    }
    free(current);
    sort_content(content);
    auto_complete_rm_double(content);
}