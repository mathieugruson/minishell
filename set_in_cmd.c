/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/28 13:43:54 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_triple_pointer_len(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '|' && !is_in_quote(s, i))
		{
			count++;
			i = i + 2;
		}
		i++;
	}
	count = count + (count + 1);
	return (count);
}

char	**malloc_double_pointer(char **tab, int count, char **args)
{
	tab = ft_calloc(sizeof(char *), (count + 1));
	if (!tab)
	{
		free_doubletab(args);
		free_error_tripletab(&tab, count);
		exit (-1);
	}
	return (tab);
}

char	***malloc_cmd(char ***cmd, char **args)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && (args[i.i][0] != '|') && i.i++ > -1)
			i.counter++;
		if (i.counter > 0)
		{
			cmd[i.j] = malloc_double_pointer(cmd[i.j], i.counter, args);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && args[i.i][0] == '|' && i.i++ > -1)
			i.counter++;
		if (i.counter > 0)
		{
			cmd[i.j] = malloc_double_pointer(cmd[i.j], i.counter, args);
			i.j++;
			i.counter = 0;
		}
	}	
	return (cmd);
}

char	***fill_cmd(char ***cmd, char **args)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] != NULL && args[i.i][0] != '|')
		{	
			cmd[i.j][i.k] = args[i.i];
			i.k++;
			i.i++;
		}
		i.j++;
		i.k = 0;
		while (args[i.i] && args[i.i][0] == '|')
		{
			cmd[i.j][i.k++] = args[i.i++];
		}
		i.j++;
		i.k = 0;
	}
	free(args);
	return (cmd);
}

char	***set_in_cmd(char ***cmd, char **args, char *s)
{	
	int		triple_pointer_len;

	triple_pointer_len = ft_triple_pointer_len(s);
	cmd = ft_calloc(sizeof(char **), (triple_pointer_len + 1));
	if (!cmd)
	{
		free_doubletab(args);
		exit (-1);
	}
	cmd = malloc_cmd(cmd, args);
	cmd = fill_cmd(cmd, args);
	return (cmd);
}
