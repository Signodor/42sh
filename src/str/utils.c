/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** utils
*/

#include <stdlib.h>
#include <string.h>

char *my_strndup(char const *str, size_t n)
{
    char *res;

    if (!str || n > strlen(str))
        return (NULL);
    if (!(res = malloc(sizeof(char) * (n + 1))))
        return (NULL);
    for (size_t i = 0; i < n; i++)
        res[i] = str[i];
    res[n] = '\0';
    return (res);
}

char *my_strdup_toch(char const *str, char c)
{
    size_t len = 0;

    while (str[len] && str[len] != c)
        len++;
    return (my_strndup(str, len));
}

char *my_strdup(char const *str)
{
    if (!str)
        return (NULL);
    return (my_strndup(str, strlen(str)));
}

int my_char_contain(char c, char const *detect)
{
    for (size_t i = 0; detect[i]; i++)
        if (c == detect[i])
            return (1);
    return (0);
}

int my_strcontain(char const *str, char const *detect)
{
    for (size_t i = 0; str[i]; i++)
        if (my_char_contain(str[i], detect))
            return (1);
    return (0);
}