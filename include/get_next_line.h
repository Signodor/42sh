/*
** EPITECH PROJECT, 2018
** CPE_getnextline_2018
** File description:
** get_next_line
*/

#ifndef GET_NEXT_LINE_H

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static const int READ_SIZE = 20;

char *get_next_line(int fd);
int is_line(char const *str);
int line_length(char const *str, char c);
char *copy_and_goes(char **str);
char *char_realloc(char *str, int new_size);

#endif /* !GET_NEXT_LINE_H */