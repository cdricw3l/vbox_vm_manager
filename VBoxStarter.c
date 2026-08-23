/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBoxStarter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 14:51:33 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/23 15:20:07 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VBoxStarter.h"

char *get_list_vm(void)
{
    pid_t pd;
    int return_value;

    pd = fork();
    if (pd < 0)
    {
        perror("Fork error");
        return (NULL);

    }
    if(pd == 0)
    {
        printf("we are in children of %d\n", getppid());
        sleep(1);
        exit(1);
    }
    waitpid(pd, &return_value, 0);
    assert(WIFEXITED(return_value));
    printf("children is finished\n");

}


int main(void)
{

    char **vm_list;

    vm_list = get_list_vm();

    
}