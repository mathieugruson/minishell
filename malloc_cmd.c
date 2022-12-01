/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:30:58 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 13:32:08 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_double_pointer_cmd(char **tab, int count, char **args, t_m *var)
{
	tab = ft_calloc(sizeof(char *), (count + 1));
	if (!tab)
	{
		free(var->args_line);
		free_doubletab(var->env);
		free_doubletab(args);
		free_error_tripletab(&tab, count);
		exit (-1);
	}
	return (tab);
}

char	***malloc_cmd(char ***cmd, char **args, t_m *var)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && (args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>') && i.i++ > -1)
			i.counter++;
		if (args[i.i] && args[i.i][0] == '|')
		{		
			cmd[i.j] = malloc_double_pointer_cmd(cmd[i.j], i.counter, args, var);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && args[i.i][0] == '|')
			i.i++;
		while (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
			i.i = i.i + 2;
	}
	cmd[i.j] = malloc_double_pointer_cmd(cmd[i.j], i.counter, args, var);	
	return (cmd);
}