/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** magic_launch
*/


#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "str.h"
#include "command.h"
#include "errors.h"
#include "utils.h"

static void update_redir(command_t *command, int fd)
{
    if (command->out.type == R_STANDARD) {
        command->out.type = R_PIPE;
        command->out.fd = fd;
    } else if (command->out.type == R_PIPE)
        update_redir(command->out.dir, fd);
    if (command->success)
        update_redir(command->success, fd);
    if (command->fail)
        update_redir(command->fail, fd);
}

static void singlelaunch(char *com, int fd)
{
    vector_t *list = vector_create();

    parse(list, com, false);
    while (list->size) {
        update_redir(list->elements[0], fd);
        launch(list->elements[0]);
        command_destroy(list->elements[0]);
        vector_pop_at(list, 0);
    }
    vector_delete(list);
    free(com);
}

ssize_t get_magic_len(int fd)
{
    ssize_t get = 0;
    ssize_t len = 0;
    char buff[32];

    while ((get = read(fd, buff, 32)) == 32)
        len += get;
    len += get;
    return (len);
}

char *get_magic_res(char *com)
{
    int fd = create_tmp_file();
    char buff[32];
    ssize_t len = 0;
    char *res;

    if (fd == -1)
        return (NULL);
    singlelaunch(com, fd);
    lseek(fd, 0, SEEK_SET);
    len = get_magic_len(fd);
    lseek(fd, 0, SEEK_SET);
    res = my_malloc(sizeof(char) * (len + 1));
    if (read(fd, res, len) != len) {
        free(res);
        return (NULL);
    }
    res[len] = 0;
    if (len && res[len - 1] == '\n')
        res[len - 1] = 0;
    close(fd);
    return (res);
}
