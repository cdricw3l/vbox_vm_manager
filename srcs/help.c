/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 02:58:09 by cdric.b           #+#    #+#             */
/*   Updated: 2026/08/24 03:36:22 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/VBoxStarter.h"

void display_help(void)
{

    printf(GRN"%-16s"BLU"-- %s"CRESET"\n", "list", "list all the vm");
    printf(GRN"%-16s"BLU"-- %s"CRESET"\n", "start --all",  "start all the vm");
    printf(GRN"%-16s"BLU"-- %s"CRESET"\n", "stop --all",  "stop all the vm");

}