/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** line
*/

#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "shell.h"
#include "env.h"
#include "alias.h"

static void pwd(char *buff, vector_t *env)
{
    char *pwd = get_env(env, "PWD");
    char *home = get_env(env, "HOME");

    if (!home) {
        if (pwd) {
            sprintf(buff + strlen(buff), "%s", pwd);
            return;
        }
        return;
    }
    for (size_t i = 0; pwd[i]; i++) {
        if (!strncmp(pwd + i, home, strlen(home))) {
            sprintf(buff + strlen(buff), "~");
            i += strlen(home) - 1;
        } else
            sprintf(buff + strlen(buff), "%c", pwd[i]);
    }
}

static void disp_username(char *buff, vector_t *env)
{
    char *username = get_env(env, "USERNAME");

    if (username) {
        sprintf(buff + strlen(buff), "%s", username);
        return;
    }
    username = get_env(env, "USER");
    if (username) {
        sprintf(buff + strlen(buff), "%s", username);
        return;
    }
    username = get_env(env, "LOGNAME");
    if (username) {
        sprintf(buff + strlen(buff), "%s", username);
        return;
    }
    sprintf(buff + strlen(buff), "none");
}

size_t display_user(char *buff, vector_t *env, int color)
{
    write(1, "\r\e[K", 4);
    disp_username(buff, env);
    sprintf(buff + strlen(buff), "\e[0m");
    sprintf(buff + strlen(buff), ":");
    sprintf(buff + strlen(buff), "\e[1;34m");
    pwd(buff, env);
    sprintf(buff + strlen(buff), "\e[0m (42sh) ");
    write(1, buff, strlen(buff));
    return (strlen(buff) - color);
}

size_t display_line(bool update, int new)
{
    static int status = 0;
    vector_t *env = get_shell()->env;
    char buff[BUFSIZ] = {0};
    int color = 15;
    static size_t size = 0;

    if (!isatty(0))
        return (printf("42sh$ "));
    if (!update && new == 84)
        return (size);
    if (update)
        alias_special("precmd");
    if (update)
        status = new;
    if (!status)
        sprintf(buff, "\e[1;32m");
    else
        sprintf(buff, "\e[31;1;5m");
    color += strlen(buff);
    return (size = display_user(buff, env, color));
}
