/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** auto_complete_sys
*/

#ifndef AUTO_COMPLETE_SYS_H_
#define AUTO_COMPLETE_SYS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "command.h"
#include "str.h"
#include "vector.h"
#include "shell.h"
#include "builtins.h"

typedef struct content_s
{
    char *name;
    char type;
    struct content_s *prev;
    struct content_s *next;
}content_t;

typedef struct auto_complete_s
{
    content_t *content;
    int size;
}auto_complete_t;

//type:
//0 == complete
//1 == display
//is_cmd:
//0 not command -> only on the actual folder
//1 command -> actual folder + /bin folder
char *auto_complete_system(char *current, int type, shell_t *shell, int is_cmd);

char *get_folder(char *current, auto_complete_t *content);
char *get_current_path(char *str, auto_complete_t *content);

int my_tablen(int **tab);

void display_content(auto_complete_t *content);

void get_content(char *folder, auto_complete_t *content, vector_t *env);
void add_bin(auto_complete_t *content, shell_t *shell);
void add_folder(char *name, auto_complete_t *content, char type, char *folder);

void clean_content(auto_complete_t *content, char *current, char *full_current,
int is_cmd);

void destroy_content(content_t *content);
char *destroy_auto_complete(auto_complete_t *content);
void content_pop(content_t *temp, auto_complete_t *content);

content_t *new_content(char *name);

auto_complete_t *init_auto_complete(void);

char *clean_current_path(char *current_path);
vector_t *auto_complete_get_path(vector_t *env);
void mv_left_arr(char *str);

char *auto_complete_set_result(auto_complete_t *content, char *current,
char *current_file);

int is_folder(char *str, char type);
int is_folder_type(char *name, char *folder, char type);
int is_folder_cmd(char *folder);

int auto_complete_is_cmd(char *cmd);
char *clean_full_cmd(char *cmd, int change_tilt);
char *get_beg_cmd(char *current_cmd);

void auto_complete_get_alias(auto_complete_t *content, shell_t *shell);

void sort_content(auto_complete_t *content);
int content_size(auto_complete_t *content);

int is_symlink(char *name, char *folder, char type);

int is_executable(char *name, char *folder, char type);

int is_tty(char *name, char *folder, char type);

int is_block(char *name, char *folder, char type);

int is_fifo(char *name, char *folder, char type);

vector_t *content_type_to_vector(auto_complete_t *content,
size_t *max_size, size_t col);
vector_t *content_name_to_vector(auto_complete_t *content,
size_t *max_size, size_t col);

void auto_complete_remplace_tild(char *current_cmd, char *res);

void auto_complete_add_builtin(auto_complete_t *content, shell_t *shell);

bool move_auto_completion(int value);

char *end_space(auto_complete_t *content, char *res);

int sort_conditions(char *curr, char *next, int i, int k);
int sort_break_condition(char *curr, char *next, int i, int k);

#endif /* !AUTO_COMPLETE_SYS_H_ */
