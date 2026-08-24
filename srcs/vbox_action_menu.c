/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbox_action_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 18:43:28 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/24 04:00:16 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/VBoxStarter.h"







static int get_commande(char *input)
{
    if (!ft_strncmp(input, "h", strlen(input)) || !ft_strncmp(input, "help", strlen(input)))
        return (CMD_HELP);
    else if (!ft_strncmp(input, "list", strlen(input)))
        return (CMD_LIST);
    else if (!ft_strncmp(input, "start --all", strlen(input)))
        return (CMD_START_ALL);
    else if (!ft_strncmp(input, "stop --all", strlen(input)))
        return (CMD_STOP_ALL);
    return (ERR);
}

int process_buffer_menu(char *input, char **vm_list)
{
    int cmd;
    (void) input;
    (void) vm_list;

    cmd = get_commande(input);

    switch (cmd)
    {
        case CMD_HELP:
        {
            display_help();
            return (OK);
        }
        case CMD_LIST:
            display_vm_list(vm_list);
        // case CMD_START_ALL:
        //     action_all_vm(vm_list, START);
        // case CMD_STOP_ALL:
        //     action_all_vm(vm_list, STOP);
        
    }

    // split = control_input(input, ft_split_len(vm_list))
    // if (!split)
    //     return (ERR);
    //ft_split_clean(&split);
    return (OK);
}


int menu(char **vm_list)
{
    int b_read;
    char buffer[BUFFER_SIZE];
    
    while (1)
    {
        write(STDOUT_FILENO, "vm to run (help -> h): ", strlen("vm to run (help -> h): "));

        b_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (b_read <= 0)
            break ;
        buffer[b_read - 1] = 0;
        if (!ft_strncmp(buffer, "quit", strlen(buffer)))
            break ;
        else if (process_buffer_menu(buffer, vm_list) == ERR)
        {
            error_msg(PROCESSING_BUFFER_MENU);
            return (ERR);
        }
    }
    return (OK);
}