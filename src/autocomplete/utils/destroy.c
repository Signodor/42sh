/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** destroy
*/

#include "auto_complete_sys.h"

void destroy_content(content_t *content)
{
    if (!content)
        return;
    if (content->name)
        free(content->name);
    free(content);
}

void content_pop(content_t *temp, auto_complete_t *content)
{
    if (!temp)
        return;
    content->size--;
    if (!temp->prev) {
        content->content = temp->next;
        if (content->content)
            content->content->prev = NULL;
        destroy_content(temp);
        return;
    }
    if (temp->next)
        temp->next->prev = temp->prev;
    if (temp->prev)
        temp->prev->next = temp->next;
    destroy_content(temp);
}

char *destroy_auto_complete(auto_complete_t *content)
{
    if (!content)
        return (NULL);
    while (content->content)
        content_pop(content->content, content);
    free(content);
    return (NULL);
}