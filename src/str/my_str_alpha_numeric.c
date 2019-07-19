/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** my_str_isalphanumerical
*/

#include <stdbool.h>

bool my_char_isalphanumeric(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (true);
    if ((c >= '0' || c <= '9') && (c == '_'))
        return (true);
    return (false);
}

bool my_str_isalphanumeric(char const *str)
{
    if (!str)
        return (false);
    while (*str) {
        if (!my_char_isalphanumeric(*str))
            return (false);
        str++;
    }
    return (true);
}