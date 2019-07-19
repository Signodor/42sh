/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** vector
*/

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <unistd.h>


typedef struct
{
    size_t size;
    size_t allocated;
    void **elements;
} vector_t;

/* Create a new vector.
Return the Object if it sucess or NULL otherwise. */
vector_t *vector_create(void);

/* Destroy the vector send in parameter.
Return 0 in case of sucess or -1 otherwise. */
int vector_delete(vector_t *vector);



/* Reallocating the vector (unsafe to use yourself, you could lost data).
Return 0 in case of sucess or -1 otherwise. */
int vector_realloc(vector_t *vector, int many);

/* Move data from start id to end id by dec movements.
Return 0 in case of sucess or -1 otherwise. */
int vector_move(vector_t *vector, int start, int end, int dec);



/* Add content at the end of the vector.
Return 0 in case of sucess or -1 otherwise. */
int vector_append(vector_t *vector, void *content);

/* Add content at the start of the vector.
Return 0 in case of sucess or -1 otherwise. */
int vector_insert(vector_t *vector, void *content);

/* Add content at id position of the vector.
Return 0 in case of sucess or -1 otherwise. */
int vector_insert_at(vector_t *vector, void *content, int id);



/* Remove last content of the vector.
Return the content in case of sucess or NULL otherwise. */
void *vector_pop(vector_t *vector);

/* Remove id content of the vector.
Return the content in case of sucess or NULL otherwise. */
void *vector_pop_at(vector_t *vector, int id);

/* Remove content by adress of the vector.
Return the content in case of sucess or NULL otherwise. */
void *vector_pop_this(vector_t *vector, void *content);



/* Launch the function for every element in the vector list.
Return the 0 in case of sucess or -1 otherwise. */
int vector_for_each(vector_t *vector, void (* function)(void *, int));

/* Launch the function for every element in the vector list without the id.
Return the 0 in case of sucess or -1 otherwise. */
int vector_for_witch(vector_t *vector, void (* function)(void *));


#endif /* !VECTOR_H_ */
