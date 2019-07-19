/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** conditionnals
*/

#include <string.h>
#include "command.h"
#include "control.h"
#include "str.h"

int con_fail(command_t *command, char **content)
{
    if (!(command->fail = command_parse(content)))
        return (-1);
    return (0);
}

int con_success(command_t *command, char **content)
{
    if (!(command->success = command_parse(content)))
        return (-1);
    return (0);
}