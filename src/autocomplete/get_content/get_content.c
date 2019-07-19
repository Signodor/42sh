/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_content
*/

#include "auto_complete_sys.h"

void add_folder_content(auto_complete_t *content, char *path)
{
    DIR *directory = opendir(path);
    struct dirent *read = NULL;

    if (!directory)
        return;
    while ((read = readdir(directory))) {
        if (read->d_name)
            add_folder(read->d_name, content, read->d_type, NULL);
        if (read->d_name && !content->content->type)
            content->content->type = 'b';
    }
    closedir(directory);
}

void add_bin(auto_complete_t *content, shell_t *shell)
{
    vector_t *path = auto_complete_get_path(shell->env);
    char *temp = NULL;

    if (!path)
        return;
    for (size_t i = 0; i < path->size; i++) {
        if (((char *)path->elements[i])[strlen(path->elements[i])] != '/')
            temp = my_strcat(my_strdup(path->elements[i]), "/");
        else
            temp = my_strdup(path->elements[i]);
        free(path->elements[i]);
        path->elements[i] = NULL;
        add_folder_content(content, temp);
        free(temp);
    }
    vector_delete(path);
}

void add_folder(char *name, auto_complete_t *content, char type, char *folder)
{
    content_t *new = new_content(my_strdup(name));
    int (*is_type[6])(char *, char *, char) = {is_folder_type, is_symlink,
    is_tty, is_block, is_fifo, is_executable};
    char chr_type[6] = {'/', '@', '%', '#', '|', '*'};

    content->size++;
    new->next = content->content;
    if (content->content)
        content->content->prev = new;
    content->content = new;
    if (type == -1)
        return;
    for (int i = 0; i < 6; i++) {
        if ((i == 0 || folder != NULL) && is_type[i](name, folder, type)) {
            new->type = chr_type[i];
            return;
        }
    }
}

void get_content(char *folder, auto_complete_t *content, vector_t *env)
{
    DIR *directory;
    struct dirent *read;

    if (!folder)
        return;
    directory = opendir(folder);
    if (!directory)
        return;
    while ((read = readdir(directory)))
        if (read->d_name)
            add_folder(read->d_name, content, read->d_type, folder);
    closedir(directory);
}