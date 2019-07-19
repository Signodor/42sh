/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** vector
*/

#include "vector.h"

int vector_realloc(vector_t *vector, int many)
{
    void **elements = malloc(sizeof(void *) * (vector->allocated + many));

    if (!elements)
        return (-1);
    for (int i = 0; i < vector->allocated + many; i++)
        elements[i] = NULL;
    if (vector->elements) {
        for (int i = 0; i < vector->allocated; i++)
            elements[i] = vector->elements[i];
        free(vector->elements);
    }
    vector->elements = elements;
    vector->allocated += many;
    return (0);
}

vector_t *vector_create(void)
{
    vector_t *vector = malloc(sizeof(vector_t));

    if (!vector)
        return (NULL);
    vector->elements = NULL;
    vector->allocated = 0;
    vector->size = 0;
    if (vector_realloc(vector, 16))
        return (NULL);
    return (vector);
}

int vector_delete(vector_t *vector)
{
    if (!vector)
        return (-1);
    if (vector->elements)
        free(vector->elements);
    free(vector);
    return (0);
}
