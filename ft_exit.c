/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:34:02 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/05 14:01:10 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_m *var, char **cmd)
{
	// ft_putdoubletab(cmd);
	// printf("cmd[2] : %s\n", cmd[2]);
	if (cmd[1] && cmd[2])
	{
		write(1, "exie: too many arguments\n", 25); // voir s'il faut modifier le numero std
		var->status = 1;
		// kill le process
	}
	else if (cmd[1] && is_str_digit(cmd[1]) != 0)
		{   
		write(2, "exit : ", 8);
		write(2, cmd[1], ft_strlen(cmd[1]));    
		write(2, ": numeric argument required\n", 26);
		var->status = 2;
		exit(var->status);
	}
	else if (!cmd[1])
	{
		var->status = 0;
		exit(var->status);
	}
	else if (cmd[1] && is_str_digit(cmd[1]))
	{
		var->status = ft_atoi(cmd[1]);
		exit (var->status);
	}
}
