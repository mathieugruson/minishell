/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:31:07 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 13:32:17 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_double_pointer_redir(char **tab, int count, char **args, t_m *var)
{
	tab = ft_calloc(sizeof(char *), (count + 1));
	if (!tab)
	{
		free(var->args_line);
		free_doubletab(var->env);
		free_doubletab(args);
		free_tripletab(var->cmd);
		free_error_tripletab(&tab, count);
		exit (-1);
	}
	return (tab);
}

char	***malloc_redir(char ***redir, char **args, t_m *var)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>')
		{
			i.i++;
		}
		if (args[i.i] && args[i.i][0] == '|')
		{		
			redir[i.j] = malloc_double_pointer_redir(redir[i.j], i.counter, args, var);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && args[i.i][0] == '|')
			i.i++;
		while (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
		{
			i.i = i.i + 2;
			i.counter = i.counter + 2;
		}
	}
	redir[i.j] = malloc_double_pointer_redir(redir[i.j], i.counter, args, var);		
	return (redir);
}