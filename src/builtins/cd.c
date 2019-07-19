/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cd
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "env.h"
#include "vector.h"
#include "str.h"
#include "alias.h"

char *replace_tilt(char *path, vector_t *env)
{
    char *home = get_env(env, "HOME");
    char *res;
    size_t len = 0;
    size_t idx = 0;

    if (!home)
        return (path);
    for (size_t i = 0; path[i]; i++)
        len += path[i] == '~';
    res = malloc(sizeof(char) * (len * (strlen(home) - 1) + strlen(path) + 1));
    for (size_t i = 0; path[i]; i++) {
        if (path[i] == '~') {
            strcpy(res + idx, home);
            idx += strlen(home) - 1;
        } else
            res[idx] = path[i];
        idx++;
    }
    res[idx] = 0;
    free(path);
    return (res);
}

void update_pwd(vector_t *env)
{
    if (!get_env(env, "PWD")) {
        set_env(env, my_strdup("PWD"), getcwd(NULL, 0));
        return;
    }
    if (!get_env(env, "OLDPWD"))
        set_env(env, my_strdup("OLDPWD"), my_strdup(get_env(env, "PWD")));
    else
        set_env(env, "OLDPWD", my_strdup(get_env(env, "PWD")));
    set_env(env, "PWD", getcwd(NULL, 0));
}

int my_cd(char **argv, vector_t *env)
{
    char *path = argv[1];

    if (!path)
        path = my_strdup("~");
    if (get_env(env, "HOME") && strcmp(path, "-"))
        path = replace_tilt(my_strdup(path), env);
    if (path && strcmp(path, "-") == 0)
        if (!(path = my_strdup(get_env(env, "OLDPWD"))))
            return (-1);
    if (!(chdir(path))) {
        alias_special("cwdcmd");
        update_pwd(env);
    } else
        fprintf(stderr, "%s: %s.\n", path, strerror(errno));
    return (0);
}