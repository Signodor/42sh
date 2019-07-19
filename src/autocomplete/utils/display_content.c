/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** display_content
*/

#include "auto_complete_sys.h"
unsigned short get_col(void);

size_t get_biggest_word(auto_complete_t *content)
{
    content_t *temp = content->content;
    size_t res = 0;
    size_t size_temp = 0;

    while (temp) {
        size_temp = strlen(temp->name);
        size_temp += 1;
        res = (size_temp > res) ? size_temp : res;
        temp = temp->next;
    }
    return (res);
}

size_t get_max_col(size_t max_size)
{
    unsigned short col = get_col();
    size_t res = 0;

    res = col / (max_size + 2);
    return (res);
}

void auto_complete_display_space(int index, int is_last,
size_t max_size, vector_t *name)
{
    if (is_last)
        return;
    if ((size_t)index < name->size)
        for (size_t k = strlen((char *)name->elements[index]);
        k < max_size; k++)
            printf(" ");
}

void auto_complete_display_file(size_t index, vector_t *name, vector_t *type)
{
    char type_content = 0;

    if (index < name->size && index < type->size) {
        move_auto_completion(true);
        type_content = *((char **)type->elements)[index];
        printf("%s", (char *)name->elements[index]);
        if (type_content != 'b' && type_content)
            printf("%c", type_content);
        else
            printf(" ");
    }
}

void display_content(auto_complete_t *content)
{
    size_t max_size = get_biggest_word(content);
    size_t col = get_max_col(max_size);
    size_t nb_files = content_size(content);
    vector_t *name = content_name_to_vector(content, &nb_files, col);
    vector_t *type = content_type_to_vector(content, &nb_files, col);
    size_t nb_file_col = nb_files / col;

    if (nb_files <= 0)
        return;
    printf("\n");
    for (size_t i = 0; i <= nb_file_col; i++) {
        for (size_t j = 0; j < col; j++) {
            auto_complete_display_file(i + j + j * nb_file_col, name, type);
            auto_complete_display_space(i + j + j * nb_file_col,
            (j == col - 1) ? 1 : 0, max_size, name);
        }
        printf("\n");
    }
    vector_delete(name);
    vector_delete(type);
}