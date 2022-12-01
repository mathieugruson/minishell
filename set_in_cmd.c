/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 13:32:02 by mgruson          ###   ########.fr       */
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
	count = count + 1;
	return (count);
}

char	***fill_cmd(char ***cmd, char **args, char ***redir)
{
	t_index	i;

	i = initialize_index();
	while (args[i.i])
	{
		while (args[i.i] && (args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>'))
			cmd[i.j][i.k++] = args[i.i++];
		if (args[i.i] && (args[i.i][0] == '<' || args[i.i][0] == '>'))
		{
			redir[i.i1][i.i2++] = args[i.i++];
			redir[i.i1][i.i2++] = args[i.i++];
		}
		if (args[i.i] && args[i.i][0] == '|' && i.i++ > -1)
		{
			i.k = 0;
			i.j++;
			i.i1++;
			i.i2 = 0;
		}
	}
	free(args);
	return (cmd);
}

void	set_in_cmd(char ****cmd, char ****redir, char **args, t_m *var)
{	
	int		triple_pointer_len;

	triple_pointer_len = ft_triple_pointer_len(var->args_line);
	*cmd = ft_calloc(sizeof(char **), (triple_pointer_len + 1));
	if (!*cmd)
	{
		free(var->args_line);
		free_doubletab(var->env);
		free_doubletab(args);
		exit (-1);
	}
	*redir = ft_calloc(sizeof(char **), (triple_pointer_len + 1));
	if (!*redir)
	{
		free(var->args_line);
		free_doubletab(var->env);
		free_tripletab(*cmd);
		free_doubletab(args);
		exit (-1);
	}
	*cmd = malloc_cmd(*cmd, args, var);
	*redir = malloc_redir(*redir, args, var);
	*cmd = fill_cmd(*cmd, args, *redir);
}
