/*
** EPITECH PROJECT, 2019
** PSU_my_autocomplete
** File description:
** get_alias
*/

#include "auto_complete_sys.h"
#include "alias.h"

void auto_complete_get_alias(auto_complete_t *content, shell_t *shell)
{
    char *temp = NULL;

    for (size_t i = 0; i < shell->aliases->size; i++) {
        temp = my_strdup(((alias_t *)shell->aliases->elements[i])->name);
        add_folder(temp, content, -1, NULL);
        if (!content->content->type)
            content->content->type = 'b';
        free(temp);
    }
}