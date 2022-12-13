/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:46:44 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/13 12:54:41 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putdoubletab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		write(1, "\n", 2);
		i++;
	}	
}

void	ft_puttripletab(char ***test)
{
	int	i;

	i = 0;
	if (!test)
		return ;
	while (test[i])
	{
		ft_putdoubletab(test[i]);
		i++;
	}
}

int	ft_puttriplelen(char ***test, t_m *var)
{
	var->tablen = 0;
	if (!test || !*test)
		return (var->tablen);
	if (!*test[0])
		return (var->tablen);
	while (test[var->tablen] != NULL)
		var->tablen++;
	return (var->tablen);
}
