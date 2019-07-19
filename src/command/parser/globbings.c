/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** globbings
*/

#include <glob.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "vector.h"
#include "str.h"
#include "errors.h"
#include "command.h"

int glob_arg(command_t *command, vector_t *args, char *arg)
{
    glob_t globbuf;

    globbuf.gl_offs = 1;
    glob(arg, GLOB_DOOFFS, NULL, &globbuf);
    if (!globbuf.gl_pathc) {
        globfree(&globbuf);
        if (args->size)
            return (error_param_int(args->elements[0], "No match."));
        return (error_param_int(arg, "No match."));
    }
    command->nb_args += globbuf.gl_pathc;
    for (size_t i = 0; i <= globbuf.gl_pathc; i++)
        vector_append(args, my_strdup(globbuf.gl_pathv[i]));
    globfree(&globbuf);
    return (0);
}

bool is_builtin_globable(vector_t *args, char *arg)
{
    char *com;

    if (!args->size)
        return (true);
    com = args->elements[0];
    if (!strcmp(com, "unsetenv"))
        return (false);
    return (true);
}

bool is_globable(vector_t *args, char *arg)
{
    int quoted = 0;
    bool open_hook = false;

    if (!is_builtin_globable(args, arg))
        return (false);
    for (size_t i = 0; arg[i]; i++) {
        if (update_quoted(&quoted, arg[i]) || quoted)
            continue;
        if (arg[i] == '*' || arg[i] == '?')
            return (true);
        open_hook = arg[i] == '[' ? true : open_hook;
        if (arg[i] == ']' && open_hook)
            return (true);
    }
    return (false);
}