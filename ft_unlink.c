/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unlink.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:38:45 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/05 16:18:46 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink(char ***redir, int i)
{
	int j;
	
	j = 0;
	while (redir[i][j])
	{
		if (ft_strncmp(redir[i][j], ".heredoc", 5) == 0)
		{
			printf("c1111 %s\n", redir[i][j]);
			unlink(redir[i][j]);
		}
		j++;
	}
}