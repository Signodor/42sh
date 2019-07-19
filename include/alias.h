/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#ifndef ALIAS_H_
#define ALIAS_H_

#include "vector.h"
#include "linked.h"

struct alias
{
    char *name;
    wordent_t *cmd;
};

/*
** alias.c
*/

int alias(char **argv, vector_t *env);
void unalias_this(vector_t *aliases, alias_t *alias);
int unalias(char **argv, vector_t *env);


/*
** display.c
*/

void print_alias_cmd(alias_t *alias);
void print_alias(alias_t *alias);
void print_all_alias(vector_t *aliases);
void print_spe_alias(vector_t *aliases, char *name);


/*
** getter.c
*/

alias_t *get_alias_name(vector_t *aliases, char *name);
void alias_special(char *name);

#endif /* !ALIAS_H_ */
