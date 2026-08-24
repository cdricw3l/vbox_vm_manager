/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbox_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 03:59:38 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/24 04:00:20 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/VBoxStarter.h"

void display_vm_list(char **vm_list)
{
    int i;
    char *name;
    char *uuid;
    
    i = 0;
    while(vm_list[i])
    {
       
        name = ft_substr(vm_list[i], 1, ft_index_of(&vm_list[i][1], 34));
        uuid = ft_substr(vm_list[i], ft_index_of(vm_list[i], '{') + 1, strlen(vm_list[i]) - (2 + ft_index_of(vm_list[i], '{')));
        printf(BMAG"%-4d"CRESET"%-16s UUID %-16s\n", i, name, uuid);
        free(name);
        free(uuid);
        i++;
    }
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
        {
            printf("start vm\n");
            //start_vm(name);
        }
        else if (action == STOP)
        {
            printf("stop vm\n");
            //stop_vm(name);
        }
        free(name);
        ptr++;
    }
    return (OK);
}