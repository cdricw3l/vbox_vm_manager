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


typedef enum E_ERROR
{
    PROCESSING_BUFFER,
    INVALIDE_PATH
    
} T_ERROR;

typedef enum E_COMMANDE
{
    CMD_LIST_VM
    
} T_COMMANDE;


int error_msg(int err_code);

#endif