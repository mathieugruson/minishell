/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:28:56 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 17:49:56 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_last_env(t_m *var)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	// printf("c4bis0\n");
	// printf("c4bis1\n");
	if (!var->cmd || !var->cmd[i] || !var->cmd[i][j])
	{
		// printf("c4bis0\n");
		return (0);
	}
	// printf("c4bis\n");
	while (var->cmd[i])
	{
		// printf("c4ter\n");
		// printf("c4ter %s\n", var->cmd[i][j]);
		j = 0;
		while (var->cmd[i][j])
			j++;
		i++;
	}
	export_env("_=", var->cmd[i - 1][j - 1], var);
	return (1);
}
