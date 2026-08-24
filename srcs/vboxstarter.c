/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vboxstarter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 14:51:33 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/24 03:59:11 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/VBoxStarter.h"

int clean_vm_list(char **vm_list)
{
    while (*vm_list)
    {
        free(*vm_list);
        vm_list++;
    }
    return (OK);
}

static int is_path_valide(char *path)
{
    if (!access(path, X_OK))
        return (OK);
    return (ERR);
}



int main(void)
{
    char *vm_list[VM_LIST_SIZE_MAX];
    
    if (is_path_valide(PATH) == ERR)
        return (error_msg(INVALIDE_PATH));
    *vm_list = NULL;
    get_list_vm(vm_list);
    menu(vm_list);
    //ft_split_display(vm_list, STDOUT_FILENO);
    clean_vm_list(vm_list);
    return (0);
}