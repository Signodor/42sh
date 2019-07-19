/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** auto_complete
*/

#ifndef auto_complete_H_
#define auto_complete_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

char *auto_complete(char *current_cmd, int is_ctrl_d);
bool move_auto_completion(int value);

#endif /* !auto_complete_H_ */