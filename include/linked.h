/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** linked
*/

#ifndef LINKED_H_
#define LINKED_H_

#include "typedefs.h"

struct wordent
{
    char *word;
    struct wordent *prev;
    struct wordent *next;
};


/*
** append.c
*/

wordent_t *linked_append(wordent_t *wordent, char *word);
wordent_t *linked_insert(wordent_t *wordent, char *word);
void linked_app(wordent_t *wordent, char *word);
void linked_ins(wordent_t *wordent, char *word);
void linked_free(wordent_t *wordent);


/*
** display.c
*/

void linked_disp(wordent_t *wordent);


/*
** aliases.c
*/

int set_aliases(wordent_t **wordent_ptr);


/*
** ending.c
*/

char *linked_concaten(wordent_t *wordent);


/*
** popper.c
*/

void linked_pop(wordent_t *wordent);
void linked_pop_last(wordent_t *wordent);


#endif /* !LINKED_H_ */
