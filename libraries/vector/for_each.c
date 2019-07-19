/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** for_each
*/

#include "vector.h"

int vector_for_each(vector_t *vector, void (* function)(void *, int))
{
    if (!vector || !function)
        return (-1);
    for (int i = 0; i < vector->size; i++)
        function(vector->elements[i], i);
    return (0);
}

int vector_for_witch(vector_t *vector, void (* function)(void *))
{
    if (!vector || !function)
        return (-1);
    for (int i = 0; i < vector->size; i++)
        function(vector->elements[i]);
    return (0);
}