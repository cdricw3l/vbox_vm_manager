/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBoxStarter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 14:51:33 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/23 15:45:56 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VBoxStarter.h"

#define CMD "VBoxManage list vms"
#define PATH "/usr/local/bin/VBoxManage"

char **get_list_vm(void)
{
    pid_t pd;
    int tube[2];
    int return_value;

    printf("we are in parent befort fork %d\n", getpid());
    if (pipe(tube) < 0)
    {
        perror("Pipe error");
        return (NULL);
    }
    pd = fork();
    if (pd < 0)
    {
        perror("Fork error");
        return (NULL);
        
    }
    if(pd == 0)
    {
        close(tube[0]);
        dup2(STDOUT_FILENO, tube[1]);
        printf("we are in children %s\n", CMD);
        char *arg[] = {"VBoxManage", "list", "vms", NULL};
       if (execve(PATH, arg, NULL) < 0)
       {
            printf("Error value: %d\n", errno);
            perror("execve error");
            exit(errno);
       }
    }
    close(tube[1]);
    dup2(tube[0], STDOUT_FILENO);
    close(tube[0]);
    waitpid(pd, &return_value, 0);
    assert(WIFEXITED(return_value));
    printf("children is finished %d\n" , WEXITSTATUS(return_value));
    printf("End\n");
    return (NULL);
}


int main(void)
{
    
    char **vm_list;

    vm_list = get_list_vm();
    (void) vm_list;
    
    return (0);
    
}