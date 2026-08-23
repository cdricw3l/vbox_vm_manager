/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 17:18:56 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/23 19:51:17 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/VBoxStarter.h"

static char *get_errror_msg(int err_code)
{
    switch (err_code)
    {
        case PROCESSING_BUFFER:
            return (BRED"Error processing buffer\n"CRESET);
        case PROCESSING_BUFFER_MENU:
            return (BRED"Error processing buffer menu\n"CRESET);
        case INVALIDE_PATH:
            return (BRED"Invalide executable path for VBoxManage\n"CRESET);
        case START_ERROR:
            return (BRED"Failled to start the vm\n"CRESET);
    }
        
    return (NULL);
}

int error_msg(int err_code)
{
    char *err_msg;
    
    err_msg = get_errror_msg(err_code);
    write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
    return (err_code);
}
