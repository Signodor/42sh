/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** env
*/

#ifndef ENV_H_
#define ENV_H_

#include "vector.h"
#include "typedefs.h"

struct env
{
    char *name;
    char *value;
};

/*
** env.h
*/

vector_t *env_create(char *envp[]);
void env_destroy(vector_t *list);
void set_env(vector_t *vec, char *name, char *value);
void unset_env(vector_t *vec, char *name);
char *get_env(vector_t *vec, char *name);
char **get_envp(vector_t *vec);
void disp_env(vector_t *env, char sep);


/*
** local.c
*/

void add_local_var(shell_t *shell, char *cmd);
void rm_local_var(shell_t *shell, char *cmd);
char *replace_local_variables(shell_t *shell, char *cmd);


/*
** get_variable.c
*/

char *get_variable_value(char *name);
char *set_variable(char *arg);


/*
** specials_varaibles.c
*/

void special_variables(void);
void create_special_variable(char *var_env, char *var_local);

/*
** verif_specials_variables.c
*/

int verif_specials_variables(void);
int is_exist(char *argv, char *var_env);
int check_name(env_t *local, char *env_var);
int check_value(char *value, env_t *local);


/*
** variable_ignoreeof.c
*/

int ignoreeof(void);

#endif /* !ENV_H_ */
