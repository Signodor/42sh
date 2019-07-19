/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** str
*/

#ifndef STR_H_
#define STR_H_

#include <unistd.h>
#include <stdbool.h>

/*
** word.c
*/

bool is_escape(char c);
void skip_escape(char **content);
bool empty_line(char *content);
char *get_next_word(char *arg);
char *dup_to_space(char **content);

/*
** utils.c
*/

char *my_strndup(char const *str, size_t n);
char *my_strdup(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strdup_toch(char const *str, char c);
char *my_str_replace(char *str, char *to_replace, char *replacing);
int my_char_contain(char c, char const *detect);
int my_strcontain(char const *str, char const *detect);


/*
** controls.c
*/

bool is_control(char *str);
char *dup_control(char *str);


/*
** arg.c
*/

char *get_arg(char **content, int *status);


/*
** str_to_tab.c
*/

char **str_to_tab(char const *str, char *delimiters);
void free_str_tab(char **tab);


/*
** my_str_alpha_numeric.c
*/

bool my_char_isalphanumeric(char c);
bool my_str_isalphanumeric(char const *str);


/*
** quoted.c
*/

int quoted_type(char c);
int update_quoted(int *quoted, char c);
int end_quote(int quoted);

#endif /* !STR_H_ */
