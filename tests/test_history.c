/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** test_history
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "vector.h"
#include "history.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "stdio.h"

void redirect_all_std(void)
{
    printf("redirecting\n");
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(add_histo, spaces)
{
    vector_t *vec = vector_create();

    add_histo("      ", vec);
    cr_assert_eq(vec->size, 0);
    vector_delete(vec);
}

Test(add_histo, null)
{
    vector_t *vec = vector_create();

    add_histo(NULL, vec);
    cr_assert_eq(vec->size, 0);
    vector_delete(vec);
}

Test(add_histo, simple_cmd)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    cr_assert_eq(vec->size, 1);
    cr_assert_str_eq(((histo_cmd_t *)vec->elements[0])->cmd, "ls");
    vector_delete(vec);
}

Test(histo_clean, basic_histo)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    clean_histo(vec);
    cr_assert_eq(vec->size, 0);
    vector_delete(vec);
}

Test(histo_clean, empty)
{
    vector_t *vec = vector_create();

    clean_histo(vec);
    cr_assert_eq(vec->size, 0);
    vector_delete(vec);
}

Test(get_cmd_histo, last_cmd)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!!"), "ls");
    vector_delete(vec);
}

Test(get_cmd_histo, get_cmd_error)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    cr_assert_eq(get_cmd_histo(vec, "!-12"), NULL);
    vector_delete(vec);
}

Test(get_cmd_histo, last_cmd_other_one)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!-1"), "ls");
    vector_delete(vec);
}

Test(get_cmd_histo, get_random_command)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("test", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!2"), "sl");
    vector_delete(vec);
}

Test(get_cmd_histo, get_cmd_from_string)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("test", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!l"), "ls");
    vector_delete(vec);
}

Test(get_cmd_histo, get_cmd_finding_string)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("test", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!?ls?"), "cd .. ; ls -l > /dev/null");
    vector_delete(vec);
}

Test(get_cmd_histo, not_found)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("test", vec);
    cr_assert_eq(get_cmd_histo(vec, "!?su?"), NULL);
    vector_delete(vec);
}

Test(get_cmd_histo, nothing_behind)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("test", vec);
    cr_assert_eq(get_cmd_histo(vec, "!?cd"), NULL);
    vector_delete(vec);
}

Test(get_cmd_histo, effectively_nothing_behind)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("test", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!?ls"), "ls");
    vector_delete(vec);
}

Test(get_cmd_histo, something_behind)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("test", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!?cd?"), "cd .. ; ls -l > /dev/null");
    vector_delete(vec);
}

Test(get_cmd_histo, replace_some_shit)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!^include^test^"), "ls test");
    vector_delete(vec);
}

Test(get_cmd_histo, no_histo)
{
    vector_t *vec = vector_create();

    cr_assert_eq(get_cmd_histo(vec, "!^include^test^"), NULL);
    vector_delete(vec);
}

Test(get_cmd_histo, trying_to_break_it)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!^include^test"), "ls test");
    vector_delete(vec);
}

Test(get_cmd_histo, trying_to_break_it_two)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    cr_assert_str_eq(get_cmd_histo(vec, "!^include"), "ls ");
    vector_delete(vec);
}

Test(get_cmd_histo, trying_to_break_it_three)
{
    vector_t *vec = vector_create();

    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    cr_assert_eq(get_cmd_histo(vec, "!^"), NULL);
    vector_delete(vec);
}

Test(print_histo, print_histo_telltale, .init = redirect_all_std)
{
    vector_t *vec = vector_create();
    char *args = malloc(sizeof(char) * 4);

    args[ARG_C] = 0;
    args[ARG_R] = 0;
    args[ARG_H] = 1;
    args[ARG_NB] = 0;
    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    print_histo(vec, args);
    cr_assert_stdout_eq_str("ls\nsl\ncd .. ; ls -l > /dev/null\nls include\n");
}

Test(print_histo, print_histo_reverse, .init = redirect_all_std)
{
    vector_t *vec = vector_create();
    char *args = malloc(sizeof(char) * 4);

    args[ARG_C] = 0;
    args[ARG_R] = 1;
    args[ARG_H] = 1;
    args[ARG_NB] = 0;
    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    print_histo(vec, args);
    cr_assert_stdout_eq_str("ls include\ncd .. ; ls -l > /dev/null\nsl\nls\n");
}

Test(print_histo, print_histo_with_nb_reverse, .init = redirect_all_std)
{
    vector_t *vec = vector_create();
    char *args = malloc(sizeof(char) * 4);

    args[ARG_C] = 0;
    args[ARG_R] = 1;
    args[ARG_H] = 1;
    args[ARG_NB] = 2;
    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    print_histo(vec, args);
    cr_assert_stdout_eq_str("ls include\ncd .. ; ls -l > /dev/null\n");
}

Test(print_histo, print_histo_with_nb, .init = redirect_all_std)
{
    vector_t *vec = vector_create();
    char *args = malloc(sizeof(char) * 4);

    args[ARG_C] = 0;
    args[ARG_R] = 0;
    args[ARG_H] = 1;
    args[ARG_NB] = 2;
    add_histo("ls", vec);
    add_histo("sl", vec);
    add_histo("cd .. ; ls -l > /dev/null", vec);
    add_histo("ls include", vec);
    print_histo(vec, args);
    cr_assert_stdout_eq_str("cd .. ; ls -l > /dev/null\nls include\n");
}