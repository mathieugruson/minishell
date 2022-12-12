/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:07:01 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/12 21:07:15 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int i)
{
	if (i == 1)
	{
		signal(SIGINT, handle_sigint_1); /* ctrl + c  affiche un nouveau prompt */
		signal(SIGQUIT, SIG_IGN); /* ctrl + \  ne fait rien */
	}
	if (i == 2)
	{
		signal(SIGINT, handle_sigint_2);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 3)
	{
		signal(SIGINT, handle_sigint_3);
		signal(SIGQUIT, SIG_IGN);
	}
}