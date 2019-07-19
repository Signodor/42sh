/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** get_next_line
*/

#include "get_next_line.h"

int is_line(char const *str)
{
    if (!str)
        return (0);
    for (int i = 0; str[i]; i++)
        if (str[i] == '\n')
            return (1);
    return (0);
}

int line_length(char const *str, char c)
{
    int i;

    if (!str)
        return (0);
    for (i = 0 ; str[i] && str[i] != c; i++);
    return (i);
}

char *copy_and_goes(char **str)
{
    char *ret;
    int i = 0;

    if (!line_length(*str, '\0'))
        return (NULL);
    if (!(ret = malloc(sizeof(char) * (line_length(*str, '\n') + 1))))
        return (NULL);
    for (; (*str)[i] && (*str)[i] != '\n'; i++)
        ret[i] = (*str)[i];
    ret[i] = 0;
    *str += i;
    if (*(*str) == '\n')
        (*str)++;
    return (ret);
}

char *char_realloc(char *str, int new_size)
{
    static char *last_realloc = NULL;
    char *new_str = malloc(sizeof(char) * new_size);
    int i = 0;

    if (!new_str)
        return (NULL);
    for (; i < new_size; i++)
        new_str[i] = 0;
    if (str != NULL) {
        for (i = 0; str[i]; i++)
            new_str[i] = str[i];
    }
    if (last_realloc)
        free(last_realloc);
    last_realloc = new_str;
    return (new_str);
}

char *get_next_line(int fd)
{
    static char *content = NULL;
    int length;
    int get_read = 1;
    int read_size = 200;
    char *back;

    if (read_size <= 0)
        return (NULL);
    while (!is_line(content) && get_read) {
        length = line_length(content, '\0');
        if (!(content = char_realloc(content, length + read_size + 1)))
            return (NULL);
        if ((get_read = read(fd, content + length, read_size)) == -1)
            return (NULL);
        content[length + read_size] = 0;
    }
    if (!(back = copy_and_goes(&content)))
        content = NULL;
    return (back);
}
