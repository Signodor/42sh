/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** display
*/

#include <stdio.h>
#include <stdbool.h>
#include "linked.h"

void linked_disp(wordent_t *wordent)
{
    bool first = true;

    while (wordent->prev)
        wordent = wordent->prev;
    while (wordent) {
        if (!first)
            printf(" -> ");
        printf("%s", wordent->word);
        first = false;
        wordent = wordent->next;
    }
    printf("\n");
}