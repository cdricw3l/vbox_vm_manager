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
# define VM_LIST_SIZE_MAX 100
# define ERR -1
# define OK 0

int process_buffer(char **vm_list, char *buffer)
{
    char **split;
    char **ptr;

    split = ft_split(buffer, 10);
    if (!split)
        return (ERR);
    ft_split_display(split, STDOUT_FILENO);
    ft_split_clean(&split);
    return (OK);
}


int get_list_vm(char **vm_list)
{
    pid_t pd;
    char buffer[BUFFER_SIZE];
    int tube[2];
    int return_value;
    int b_read;

    assert(*vm_list == NULL);
    if (pipe(tube) < 0)
    {
        perror("Pipe error");
        return (ERR);
    }
    pd = fork();
    if (pd < 0)
    {
        perror("Fork error");
        return (ERR);
        
    }
    if(pd == 0)
    {
        close(tube[0]);
        /* transforme STDOUT en tube[1] (write part of the pipe). Everything who is printed in STDOUT_FILENO go now in tube[1] fd */
        dup2(tube[1], STDOUT_FILENO);
        close(tube[1]);
        char *arg[] = {"VBoxManage", "list", "vms", NULL};
        if (execve(PATH, arg, NULL) < 0)
        {
                printf("Error value: %d\n", errno);
                perror("execve error");
                exit(errno);
        }
    }
    close(tube[1]);
    waitpid(pd, &return_value, 0);
    if (WEXITSTATUS(return_value) != 0)
        return (ERR);
    b_read = 1;
    while (b_read > 0)
    {
        /* we are now reading in tube[0], the read part of the pipe */
        b_read = read(tube[0], buffer, BUFFER_SIZE);
        buffer[b_read] = 0;
        if (b_read > 0)
        {
            if (process_buffer(vm_list, buffer) == ERR)
            {
                printf("Error processing buffer\n");
                close(tube[0]);
                return (ERR);
            }

            // write(STDOUT_FILENO, "[BUFFER]: ", strlen("[BUFFER]: "));
            // write(STDOUT_FILENO, buffer, b_read);
        }
    }
    close(tube[0]);
    return (OK);
}


int main(void)
{
    
    char *vm_list[VM_LIST_SIZE_MAX];
    
    *vm_list = NULL;
    get_list_vm(vm_list);

    return (0);
    
}