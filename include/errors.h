/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** errors
*/

#ifndef ERRORS_H_
#define ERRORS_H_

#define NAME "42sh"

#define ALREADY_REDIR "Ambiguous output redirect."
#define NO_REDIR_NAME "Missing name for redirect."

#define SETENV_BEGIN "setenv: Variable name must begin with a letter."
#define ENVNAME "setenv: Variable name must contain alphanumeric characters."

#define BADENV "error while loading the environment."

#define MALLOC_FAILED "not enough memory"

#define NULL_COMMAND "Invalid null command."

#define COMMAND_NOT_FOUND "Command not found."
#define PERMISSION_DENIED "Permission denied."

/*
** errors.c
*/

void error_msg(char const *att, char const *msg);
int error_int(char const *msg);
void *error_ptr(char const *msg);
int error_param_int(char const *att, char const *msg);

#endif /* !ERRORS_H_ */
