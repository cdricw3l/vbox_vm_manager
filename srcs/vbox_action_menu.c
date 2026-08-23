/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbox_action_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 18:43:28 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/23 20:05:54 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/VBoxStarter.h"

int ft_index_of(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (ERR);
}

char **control_input(char *input, int nb_vm)
{
    int i;
    int j;
    char **split;

    split = ft_split(input, 32);
    if (!split)
        return(NULL);
    i = 0;
    while (split[i])
    {
        j = 0;
        while (split[i][j])
        {
            if (!ft_isdigit(split[i][j]) || ft_atoi(split[i]) > nb_vm - 1)
            {
                ft_split_clean(&split);
                return (NULL);
            }
        }
    }
    return (split);
}

int stop_vm(char *vm_name)
{
    pid_t pid;
    int return_value;

    return_value = 0;
    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return (ERR);
    }
    if (pid == 0)
    {
        char *arg[] = {"VBoxManage" ,"controlvm", vm_name, "poweroff", NULL};
        if (execve(PATH, arg, NULL) < 0)
        {
            printf("Error value: %d\n", errno);
            perror("execve error");
            exit(errno);
        }
    }
    waitpid(pid, &return_value, 0);
    if (WEXITSTATUS(return_value) != 0)
    {
        error_msg(START_ERROR);
        return (ERR);
    }
    return (OK);
}

int start_vm(char *vm_name)
{
    pid_t pid;
    int return_value;

    return_value = 0;
    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        return (ERR);
    }
    if (pid == 0)
    {
        char *arg[] = {"VBoxManage" ,"startvm", vm_name, "--type=headless", NULL};
        if (execve(PATH, arg, NULL) < 0)
        {
            printf("Error value: %d\n", errno);
            perror("execve error");
            exit(errno);
        }
    }
    waitpid(pid, &return_value, 0);
    if (WEXITSTATUS(return_value) != 0)
    {
        error_msg(START_ERROR);
        return (ERR);
    }
    return (OK);
}


int action_all_vm(char **vm_list, int action)
{
    char **ptr;
    char *name;

    ptr = vm_list;
    while(*ptr)
    {
        /* 34 == " */
        name = ft_substr(*ptr, 1, ft_index_of(&(*ptr)[1], 34));
        assert(name);
        if (name)
            printf("Name: %s\n", name);
        if (action == START)
            start_vm(name);
        else if (action == STOP)
            stop_vm(name);
        free(name);
        ptr++;
    }
    return (OK);
}

int process_buffer_menu(char *input, char **vm_list)
{
    char **split;   

    (void) input;
    (void) vm_list;

    printf("input : %s", input);
    if (!ft_strncmp(input, "all", strlen(input)))
    {
        action_all_vm(vm_list, START);
        return (OK);
    }
    else if (!ft_strncmp(input, "stop\n", strlen(input)))
    {
        printf("input : %s\n", input);

        action_all_vm(vm_list, STOP);
        return (OK);
    }
    // split = control_input(input, ft_split_len(vm_list))
    // if (!split)
    //     return (ERR);
    ft_split_clean(&split);
    return (OK);
}

int menu(char **vm_list)
{
    int i;
    int b_read;
    char buffer[BUFFER_SIZE];
    i = 0;
    while(vm_list[i])
    {
        printf("[%d] %s\n", i, vm_list[i]);
        i++;
    }
    write(STDOUT_FILENO, "vm to run: ", strlen("vm to run: "));
    while (1)
    {
        b_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        buffer[b_read] = 0;
        if (!ft_strncmp(buffer, "quit\n", strlen(buffer)))
            break ;
        else if (process_buffer_menu(buffer, vm_list) == ERR)
        {
            error_msg(PROCESSING_BUFFER_MENU);
            return (ERR);
        }
        break ;
    }
    return (OK);
}