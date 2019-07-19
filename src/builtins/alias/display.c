/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** display
*/

#include <stdio.h>
#include <stdbool.h>
#include "builtins.h"
#include "alias.h"

void print_alias_cmd(alias_t *alias)
{
    wordent_t *current = alias->cmd;
    bool first = true;

    while (current) {
        if (!first)
            printf(" ");
        printf("%s", current->word);
        current = current->next;
        first = false;
    }
    printf("\n");
}

void print_alias(alias_t *alias)
{
    printf("%s\t", alias->name);
    print_alias_cmd(alias);
}

void print_all_alias(vector_t *aliases)
{
    for (size_t i = 0; i < aliases->size; i++)
        print_alias((alias_t *)aliases->elements[i]);
}

void print_spe_alias(vector_t *aliases, char *name)
{
    alias_t *alias = get_alias_name(aliases, name);

    if (alias)
        print_alias_cmd(alias);
}