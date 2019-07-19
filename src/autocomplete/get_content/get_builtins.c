/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_builtins
*/

#include "auto_complete_sys.h"
#include "builtins.h"
#include "builtins_models.h"

void auto_complete_add_1_builtin(auto_complete_t *content, char *name)
{
    add_folder(name, content, -1, NULL);
    content->content->type = 'b';
}

void auto_complete_add_builtin(auto_complete_t *content, shell_t *shell)
{
    for (size_t i = 0; builts[i].name; i++)
        auto_complete_add_1_builtin(content, builts[i].name);
}