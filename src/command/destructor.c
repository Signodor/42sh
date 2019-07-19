/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** destructor
*/

#include "command.h"
#include "unistd.h"

void command_destroy(command_t *command)
{
    if (!command)
        return;
    command_destroy(command->fail);
    command_destroy(command->success);
    command_destroy(command->out.dir);
    if (!command->arguments) {
        free(command);
        return;
    }
    for (size_t i = 0; command->arguments[i]; i++)
        free(command->arguments[i]);
    free(command->arguments);
    if (command->in.type == R_FILE)
        free(command->in.filepath);
    if (command->out.type == R_FILE)
        free(command->out.filepath);
    free(command);
}