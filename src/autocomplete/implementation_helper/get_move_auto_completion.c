/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_move_auto_completion
*/

#include "auto_complete_sys.h"

bool move_auto_completion(int value)
{
    static bool res = false;

    if (value == -1)
        return (res);
    if (value)
        res = true;
    else
        res = false;
    return (false);
}