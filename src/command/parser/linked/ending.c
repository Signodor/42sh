/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** ending
*/

#include <stdlib.h>
#include <string.h>
#include "linked.h"
#include "utils.h"
#include "str.h"

static size_t linked_len(wordent_t *wordent)
{
    size_t len = 0;

    while (wordent) {
        len += strlen(wordent->word) + 1;
        wordent = wordent->next;
    }
    return (len);
}

static char *final_concatenate(wordent_t *wordent, size_t len)
{
    size_t idx = 0;
    char *res = my_malloc(sizeof(char) * (len));

    while (wordent) {
        memcpy(res + idx, wordent->word, strlen(wordent->word));
        idx += strlen(wordent->word);
        res[idx++] = ' ';
        wordent = wordent->next;
    }
    res[len - 1] = 0;
    return (res);
}

char *linked_concaten(wordent_t *wordent)
{
    wordent_t *ptr_res = wordent;
    char *res;
    size_t len;

    if (!wordent)
        return (my_strdup(""));
    while (wordent->prev)
        wordent = wordent->prev;
    len = linked_len(wordent);
    res = final_concatenate(wordent, len);
    return (res);
}