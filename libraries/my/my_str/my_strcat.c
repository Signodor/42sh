/*
** EPITECH PROJECT, 2019
** my_concat_str.c
** File description:
** concat_str functions
*/

#include <stdlib.h>

int my_strlen(char *str)
{
    int size = 0;

    if (!str || !str[0])
        return (0);
    for (; str[size]; size++);
    return (size);
}

char *my_strcat(char *str1, char const *str2)
{
    char *dest = NULL;
    int i = 0;
    int j = 0;

    if (!str1 && !str2)
        return (NULL);
    dest = malloc(sizeof(char) * ((str1 ? my_strlen(str1) : 0) +
    my_strlen((char *)str2) + 1));
    if (str1 != NULL) {
        for (i = 0; str1[i] != 0; i++, j++)
            dest[j] = str1[i];
    }
    if (str2 != NULL) {
        for (i = 0; str2[i] != 0; i++, j++)
            dest[j] = str2[i];
    }
    dest[j] = 0;
    free(str1);
    return (dest);
}
