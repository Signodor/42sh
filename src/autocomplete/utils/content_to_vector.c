/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** content_to_vector
*/

#include "auto_complete_sys.h"

vector_t *content_type_to_vector(auto_complete_t *content,
size_t *max_size, size_t col)
{
    vector_t *res = vector_create();
    content_t *temp = content->content;

    while (temp) {
        vector_append(res, &temp->type);
        temp = temp->next;
    }
    while (*max_size % col) {
        *max_size = *max_size + 1;
        vector_append(res, "");
    }
    return (res);
}

vector_t *content_name_to_vector(auto_complete_t *content,
size_t *max_size, size_t col)
{
    vector_t *res = vector_create();
    content_t *temp = content->content;

    while (temp) {
        vector_append(res, temp->name);
        temp = temp->next;
    }
    while (*max_size % col) {
        *max_size = *max_size + 1;
        vector_append(res, "");
    }
    return (res);
}