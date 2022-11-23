/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:10:48 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/23 18:23:53 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_quote(char *str, int quote, int a)
{
	t_index	i;

	i = initialize_index();
	a--;
	while(str[a] != quote)
		a--;
	i.i1 = a;
	while(i.count < 2 && i.count++ > -1)
	{
		while (str[a])
		{
			if (str[a] == quote)
			{	
				while (str[a+1])
				{
					str[a] = str[a+1];
					a++;
				}
				str[a] = 0;
			}
			a++;
		}
		a = i.i1;
	}
	return (str);
}

int is_quote_in(char *str, int i)
{
	int j;

	j = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			j++;		
		i++;
	}
	if (j == 0)
		return (0);
	return (1);
}

char *clear_quote(char *str)
{
	t_index i;
	
	i = initialize_index();
	if (!is_quote_in(str, i.i))
		return (str);
	while(str[i.i])
	{
		if (str[i.i] == 34 && i.j++ > 0 && i.j == 2 && (i.k == 2 || i.k == 0))	
		{
				str = remove_quote(str, 34, i.i);
				i.j = 0;
				i.k = 0;
				i.i = i.i - 2;
		}
		else if (str[i.i] == 39 && i.k++ > 0 && i.k == 2 && (i.j == 2 || i.j == 0))
		{
				str = remove_quote(str, 39, i.i);
				i.k = 0;
				i.j = 0;
				i.i = i.i - 2;
		}
		i.i++;
	}
	return (str);
}

char ***clean_args(char ***cmd)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(cmd[i])
	{
		j = 0;
		while(cmd[i][j])
		{
			cmd[i][j] = clear_quote(cmd[i][j]);
			j++;
		}
		i++;
	}
	return (cmd);
}
