/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:10:48 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/09 11:56:02 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quote(char *str, int quote, int i)
{
	int	ibis;
	int	j;

	j = 0;
	while (str[i] != quote)
		i--;
	ibis = i;
	while (str[i] && j < 2)
	{
		if (str[i] == quote)
		{	
			while (str[i + 1])
			{
				str[i] = str[i + 1];
				i++;
			}
			str[i] = 0;
		}
		i++;
		if (!str[i] && j++ > -1)
			i = ibis;
	}
	return (str);
}

/* le -2 sert pour eviter que le i++ ligne 106 saute une quote*/

char	*clear_quote(char *str, int dq, int sq)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 && dq++ > -1 && dq == 2 && \
		(sq == 2 || sq == 0 || !is_in_quote(str, i)))
		{
			str = remove_quote(str, 34, (i -1));
			dq = 0;
			sq = 0;
			i = i - 2;
		}
		else if (str[i] == 39 && sq++ > -1 && sq == 2 && \
		(dq == 2 || dq == 0 || !is_in_quote(str, i)))
		{
			str = remove_quote(str, 39, (i - 1));
			sq = 0;
			dq = 0;
			i = i - 2;
		}
	}
	return (str);
}

char	***clean_args(char ***cmd)
{
	int	i;
	int	j;
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	i = 0;
	j = 0;
	while (cmd[i])
	{
		j = 0;
		while ((cmd[i][j] && j == 0) || (cmd[i][j] && j >= 1 && \
		ft_strcmp(cmd[i][j - 1], "<<") != 0))
		{
			cmd[i][j] = clear_quote(cmd[i][j], dq, sq);
			j++;
		}
		i++;
	}
	return (cmd);
}
