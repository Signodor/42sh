/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** control
*/

#include <string.h>
#include <stdlib.h>
#include "control.h"
#include "str.h"

const struct control controls[] = {
    {"||", &con_fail},
    {"&&", &con_success},
    {">>", &con_double_right},
    {"<<", &con_double_left},
    {"|", &con_pipe},
    {">", &con_right},
    {"<", &con_left},
    {NULL, NULL},
};

const char *char_con[] = {
    ";",
    "(",
    ")",
    NULL,
};

bool is_control(char *str)
{
    if (!str)
        return false;
    for (size_t i = 0; char_con[i]; i++)
        if (*str == *(char_con[i]))
            return true;
    for (size_t i = 0; controls[i].name; i++) {
        if (!strncmp(str, controls[i].name, strlen(controls[i].name)))
            return true;
    }
    return false;
}

int call(command_t *command, char **content, char *str)
{
    size_t index = 0;
    struct control control;
    bool found = false;

    for (; controls[index].name; index++)
        if (!strncmp(str, controls[index].name,
        strlen(controls[index].name))) {
            control = controls[index];
            found = true;
            break;
        }
    if (!found || !control.call)
        return (0);
    return (control.call(command, content));
}

char *dup_control(char *str)
{
    char const *name;

    if (!str)
        return (NULL);
    for (size_t i = 0; char_con[i]; i++)
        if (*str == *(char_con[i]))
            return (my_strdup(char_con[i]));
    for (size_t i = 0; controls[i].name; i++) {
        name = controls[i].name;
        if (!strncmp(str, name, strlen(name)))
            return (my_strdup(name));
    }
    return (NULL);
}