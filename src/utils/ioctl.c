/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** mode
*/

#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

unsigned short get_col(void)
{
    struct winsize size;

    ioctl(0, TIOCGWINSZ, &size);
    return (size.ws_col ? size.ws_col : 1);
}

unsigned short get_row(void)
{
    struct winsize size;

    ioctl(0, TIOCGWINSZ, &size);
    return (size.ws_row ? size.ws_row : 1);
}

void mode(int which)
{
    static struct termios old;
    static struct termios new;
    static int up = 0;

    if (up == 0) {
        up = 1;
        ioctl(0, TCGETS, &old);
        ioctl(0, TCGETS, &new);
        new.c_lflag &= ~ECHO;
        new.c_lflag &= ~ICANON;
    }
    if (!isatty(0))
        return;
    if (which == 0)
        ioctl(0, TCSETS, &new);
    else if (which == 1)
        ioctl(0, TCSETS, &old);
}