/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exprt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:20:35 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/23 15:55:23 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_not_in(char *str, char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(str, tab[i]) == 0)
		{
			return (0);		
		}
		i++;
	}
	return(1);
}

char **sort_envp(char **envp, char **exprt)
{
	t_index i;
	char *tmp;

	tmp = NULL;
	i = initialize_index();

	tmp = "~";
	while (ft_tablen(envp) != ft_tablen(exprt))
	{
		while (envp[i.i])
		{
			if (envp[i.i] && ft_strcmp(envp[i.i], tmp) < 0 && is_not_in(envp[i.i], exprt) == 1)
			{
				tmp = envp[i.i];
				i.l = 1;
			}
			i.i++;
		}
		if (i.l == 1)
		{
			exprt[i.k++] = tmp;
		}
		i.i1++;
		i.l = 0;
		i.i = 0;
		tmp = "~";
	}
	return (exprt);
}

char **add_export_form(char **exprt)
{
	t_index i;
	char **new_exprt;

	i = initialize_index();
	i.len = ft_tablen(exprt);
	new_exprt = ft_calloc(sizeof(char *), (i.len + 1));
	while(exprt[i.i])
	{
		new_exprt[i.i] = ft_calloc(sizeof(char), (ft_strlen(exprt[i.i]) + 9 + 1));
		new_exprt[i.i] = ft_memcpy_mathieu(new_exprt[i.i], "export ", 7);
		i.k = 7;
		i.j = 0;
		while(exprt[i.i][i.j])
		{
			new_exprt[i.i][i.k++] = exprt[i.i][i.j++];
			if (exprt[i.i][i.j-1] == '=' && i.count++ == 0)
			{
				new_exprt[i.i][i.k++] = 34;
			}
		}
		new_exprt[i.i][i.k++] = 34;
		i.count = 0;
		i.i++;
	}
	return (free(exprt), new_exprt);
}

char **get_exprt(char **envp)
{
	t_index i;
	char **exprt;
	
	i = initialize_index();
	i.len = ft_tablen(envp);
	exprt = ft_calloc(sizeof(char *), (i.len + 1));
	exprt = sort_envp(envp, exprt);
	exprt = add_export_form(exprt);
	return (exprt);
}