# ifndef VBOXSTARTER_H
# define VBOXSTARTER_H

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/errno.h>
#include <string.h>
# include "../libft/libft.h"
# include "color-codes.h"

# define PATH "/usr/local/bin/VBoxManage"
# define BUFFER_SIZE 1024
# define VM_LIST_SIZE_MAX 101
# define ERR -1
# define OK 0
#define START 0
#define STOP 1


typedef enum E_ERROR
{
    PROCESSING_BUFFER,
    PROCESSING_BUFFER_MENU,
    INVALIDE_PATH,
    START_ERROR
    
} T_ERROR;

typedef enum E_COMMANDE
{
    CMD_HELP,
    CMD_LIST,
    CMD_START_ALL,
    CMD_STOP_ALL

    
} T_COMMANDE;

int get_list_vm(char **vm_list);
int menu(char **vm_list);
void display_help(void);
int error_msg(int err_code);

/* action */
void    display_vm_list(char **vm_list);
int     stop_vm(char *vm_name);
int     start_vm(char *vm_name);
int     action_all_vm(char **vm_list, int action);
#endif