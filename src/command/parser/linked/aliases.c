/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** aliases
*/

#include <string.h>
#include "str.h"
#include "shell.h"
#include "linked.h"
#include "builtins.h"
#include "alias.h"
#include "errors.h"

static bool is_aliasable(wordent_t *wordent)
{
    char *word;

    if (!wordent->prev)
        return (true);
    word = wordent->prev->word;
    if (!strcmp(word, ";") || !strcmp(word, ";"))
        return (true);
    return (false);
}

static int follow_alias(vector_t *aliases, alias_t *alias, int limit)
{
    wordent_t *wordent = alias->cmd;
    alias_t *new;
    int status = 0;

    if (limit < 0)
        return (error_int("Alias loop."));
    while (wordent && !status) {
        if (!is_aliasable(wordent) || !strcmp(wordent->word, alias->name)) {
            wordent = wordent->next;
            continue;
        }
        new = get_alias_name(aliases, wordent->word);
        if (new)
            status = follow_alias(aliases, new, limit - 1);
        wordent = wordent->next;
    }
    return (status);
}

static wordent_t *impl_aliases(wordent_t *wordent, alias_t *alias)
{
    wordent_t *curr = alias->cmd;
    wordent_t *first_after = curr;
    wordent_t *now = wordent->prev;
    char *first = my_strdup(wordent->word);

    if (!curr)
        return (NULL);
    linked_pop(wordent);
    while (curr) {
        now = linked_append(now, my_strdup(curr->word));
        if (!strcmp(first, curr->word)) {
            curr = curr->next;
            continue;
        }
        if (set_aliases(&now))
            return (NULL);
        curr = curr->next;
    }
    return (now);
}

int set_aliases(wordent_t **wordent_ptr)
{
    vector_t *aliases = get_shell()->aliases;
    alias_t *alias;
    wordent_t *wordent = *wordent_ptr;

    while (wordent->next)
        wordent = wordent->next;
    if (!is_aliasable(wordent))
        return (0);
    if (!(alias = get_alias_name(aliases, wordent->word)))
        return (0);
    if (follow_alias(aliases, alias, 50))
        return (-1);
    if (!(*wordent_ptr = impl_aliases(wordent, alias)))
        return (-1);
    return (0);
}