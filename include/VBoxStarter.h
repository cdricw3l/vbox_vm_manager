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

typedef enum E_ERROR
{
    PROCESSING_BUFFER,
    INVALIDE_PATH
    
} T_ERROR;


int error_msg(int err_code);

#endif