/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** auto_complete
*/

#include "auto_complete_sys.h"
#include "shell.h"

char *apply_auto_complete(auto_complete_t *content, int type, char *current,
char *current_file)
{
    char *res = NULL;

    if (type || content->size != 1)
        display_content(content);
    res = auto_complete_set_result(content, current, current_file);
    destroy_auto_complete(content);
    if (res == NULL)
        res = current;
    else
        free(current);
    return (res);
}

char *auto_complete_return(char *res, char *current_cmd, int is_ctrl_d,
char *res_auto_complete)
{
    char *temp = clean_full_cmd(current_cmd, 0);

    free(res_auto_complete);
    if (is_ctrl_d) {
        free(res);
        free(temp);
        return (my_strdup(current_cmd));
    }
    if (temp && !strncmp(temp, "~/", 2))
        auto_complete_remplace_tild(current_cmd, res);
    free(temp);
    return (res);
}

char *auto_complete(char *current_cmd, int is_ctrl_d)
{
    shell_t *shell = get_shell();
    int is_cmd = auto_complete_is_cmd(current_cmd);
    char *cmd_cleaned = clean_full_cmd(current_cmd, 1);
    char *res = NULL;
    char *res_auto_cplt = NULL;

    move_auto_completion(false);
    res_auto_cplt = auto_complete_system(cmd_cleaned, is_ctrl_d,
    shell, is_cmd);
    cmd_cleaned = get_beg_cmd(current_cmd);
    res = my_strcat(cmd_cleaned, res_auto_cplt);
    cmd_cleaned = NULL;
    return (auto_complete_return(res, current_cmd, is_ctrl_d, res_auto_cplt));
}

bool auto_complete_error_gest(char *folder, char *current,
auto_complete_t *content)
{
    char *current_folder = NULL;

    if (!folder)
        return (false);
    if (!access(folder, F_OK))
        return (false);
    current_folder = get_current_path(current, content);
    fprintf(stderr, "\n%s not found\n", current_folder);
    free(current_folder);
    move_auto_completion(1);
    return (true);
}

char *auto_complete_system(char *current, int type, shell_t *shell, int is_cmd)
{
    auto_complete_t *content = init_auto_complete();
    char *folder = get_folder(current, content);
    char *current_file = clean_current_path(current);

    get_content(folder, content, shell->env);
    if (auto_complete_error_gest(folder, current, content))
        return (current);
    if (is_cmd && current && current[0] && !is_folder_cmd(folder)) {
        auto_complete_get_alias(content, shell);
        add_bin(content, shell);
        auto_complete_add_builtin(content, shell);
    }
    free(folder);
    if (!content || !content->content)
        return (destroy_auto_complete(content));
    clean_content(content, current_file, current, is_cmd);
    return (apply_auto_complete(content, type, current, current_file));
}