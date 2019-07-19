/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** pop
*/

#include "vector.h"

void *vector_pop_at(vector_t *vector, int id)
{
    void *content;

    if (!vector || !vector->elements || id < 0 || id > vector->size)
        return (NULL);
    content = vector->elements[id];
    if (id != vector->size - 1)
        if (vector_move(vector, id + 1, vector->size - 1, -1))
            return (NULL);
    vector->size--;
    return (content);
}

void *vector_pop(vector_t *vector)
{
    return (vector_pop_at(vector, 0));
}

void *vector_pop_this(vector_t *vector, void *content)
{
    int back = 0;

    if (!vector)
        return (NULL);
    for (int i = 0; i < vector->size; i++) {
        if (vector->elements[i] == content) {
            back = vector_pop_at(vector, i) == NULL;
            i = 0;
        }
        if (back)
            return (NULL);
    }
    return (content);
}