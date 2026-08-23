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

# define CMD "VBoxManage list vms"
# define PATH "/usr/local/bin/VBoxManage"
# define BUFFER_SIZE 1024

char **get_list_vm(void)
{
    pid_t pd;
    char buffer[BUFFER_SIZE];
    int tube[2];
    int return_value;
    int b_read;

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
        dup2(tube[1], STDOUT_FILENO);
        char *arg[] = {"VBoxManage", "list", "vms", NULL};
       if (execve(PATH, arg, NULL) < 0)
       {
            printf("Error value: %d\n", errno);
            perror("execve error");
            exit(errno);
       }
    }
    close(tube[1]);
    dup2(tube[0], STDIN_FILENO);
    close(tube[0]);
    waitpid(pd, &return_value, 0);
    b_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    buffer[b_read] = 0;
    write(STDOUT_FILENO, "[BUFFER]: ", strlen("[BUFFER] "));
    write(STDOUT_FILENO, buffer, b_read);
    b_read =  read(tube[0], buffer, BUFFER_SIZE);
    buffer[b_read] = 0;
    printf("voici buffer %s\n", buffer);
    return (NULL);
}


int main(void)
{
    
    char **vm_list;

    vm_list = get_list_vm();
    (void) vm_list;
    
    return (0);
    
}