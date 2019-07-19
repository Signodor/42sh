/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** append
*/

#include <stdlib.h>
#include <unistd.h>
#include "linked.h"
#include "utils.h"

wordent_t *linked_append(wordent_t *wordent, char *word)
{
    wordent_t *new = my_malloc(sizeof(wordent_t));
    wordent_t *ret_ptr = wordent;

    new->word = word;
    new->prev = NULL;
    new->next = NULL;
    if (wordent) {
        while (wordent->next)
            wordent = wordent->next;
        wordent->next = new;
        new->prev = wordent;
        return (ret_ptr);
    }
    return (new);
}

wordent_t *linked_insert(wordent_t *wordent, char *word)
{
    wordent_t *new = my_malloc(sizeof(wordent_t));
    wordent_t *ret_ptr = wordent;

    new->word = word;
    new->prev = NULL;
    new->next = NULL;
    if (wordent) {
        while (wordent->prev)
            wordent = wordent->prev;
        wordent->prev = new;
        new->next = wordent;
        return (ret_ptr);
    }
    return (new);
}

void linked_app(wordent_t *wordent, char *word)
{
    wordent_t *new;

    if (!wordent)
        return;
    new = my_malloc(sizeof(wordent_t));
    new->word = word;
    new->prev = wordent;
    new->next = wordent->next;
    wordent->next = new;
    if (new->next)
        new->next->prev = new;
}

void linked_ins(wordent_t *wordent, char *word)
{
    wordent_t *new;

    if (!wordent)
        return;
    new = my_malloc(sizeof(wordent_t));
    new->word = word;
    new->prev = wordent->prev;
    new->next = wordent;
    wordent->prev = new;
    if (new->prev)
        new->prev->next = new;
}

void linked_free(wordent_t *wordent)
{
    wordent_t *next;

    if (!wordent)
        return;
    while (wordent->prev)
        wordent = wordent->prev;
    while (wordent) {
        next = wordent->next;
        free(wordent->word);
        free(wordent);
        wordent = next;
    }
}