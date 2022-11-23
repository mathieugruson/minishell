/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exprt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:48:04 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/23 12:59:58 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_exprt(char **envp)
{
	t_index i;

	i = initialize_index();
	i.len = ft_tablen(envp);
}

int main(int argc, char **argv, char **envp)
{
	char **exprt;

	exprt = get_exprt(envp);
	return (0);
}