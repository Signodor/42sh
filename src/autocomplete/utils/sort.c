/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** sort
*/

#include "auto_complete_sys.h"

int content_size(auto_complete_t *content)
{
    content_t *temp = content->content;
    int size = 0;

    while (temp) {
        size++;
        temp = temp->next;
    }
    return (size);
}

void swap_content(content_t *elem1, content_t *elem2, auto_complete_t *content)
{
    content_t *temp = NULL;

    temp = elem1->prev;
    if (temp)
        temp->next = elem2;
    elem2->prev = temp;
    elem1->prev = elem2;
    elem1->next = elem2->next;
    elem2->next = elem1;
    if (elem1->next != NULL)
        elem1->next->prev = elem1;
    if (elem1 == content->content)
        content->content = elem2;
}

void sort_two_content(content_t *list, auto_complete_t *content)
{
    int i = 0;
    int k = 0;

    for (; list->name[i] && list->next->name[k]; i++, k++) {
        for (; list->name[i] && list->name[i] == '-'; i++);
        for (; list->next->name[k] && list->next->name[k] == '-'; k++);
        if (sort_conditions(list->name, list->next->name, i, k)) {
            swap_content(list, list->next, content);
            return;
        } else if (sort_break_condition(list->name, list->next->name, i, k))
            return;
    }
}

void sort_content(auto_complete_t *content)
{
    int size = content_size(content);
    content_t *list = NULL;

    for (int i = 0; i <= size; i++) {
        list = content->content;
        while (list && list->next) {
            sort_two_content(list, content);
            list = list->next;
        }
    }
}