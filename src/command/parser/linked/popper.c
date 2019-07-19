/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** popper
*/

#include <stdlib.h>
#include "linked.h"

void linked_pop(wordent_t *wordent)
{
    if (wordent->prev)
        wordent->prev->next = wordent->next;
    if (wordent->next)
        wordent->next->prev = wordent->prev;
    free(wordent->word);
    free(wordent);
}

void linked_pop_last(wordent_t *wordent)
{
    while (wordent->next)
        wordent = wordent->next;
    if (wordent->prev)
        wordent->prev->next = NULL;
    free(wordent->word);
    free(wordent);
}
