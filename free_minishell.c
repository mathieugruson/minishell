/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:02:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/06 12:16:05 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_m *var)
{
	if (var->redir)
		free_tripletab(var->redir);
	if (var->cmd)
		free_tripletab(var->cmd);
	if (var->env)
		free_doubletab(var->env);
	if (var->split_path)
		free_doubletab(var->split_path);
	if (var->pid)
		free(var->pid);
}

void	free_error_doubletab(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		str[i] = NULL;
		i--;
	}
	free(str);
	str = NULL;
}

void free_error_tripletab(char ***tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}	
	free(tab);
	tab = NULL;	
}

void	free_doubletab(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void free_tripletab(char ***tab)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			free(tab[i][j]);
			tab[i][j] = NULL;
			j++;
		}
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
