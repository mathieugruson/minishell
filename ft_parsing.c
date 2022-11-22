/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 14:57:02 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***ft_parsing(char *s)
{
	char	***cmd;
	char	**args;

	if (!s || s[0] == '\n')
		return (NULL);
	if (!is_cmdline_valid(s))
		return (NULL);
	args = get_args(s, ' ');
	if (!args)
		return (NULL);	
	cmd = NULL;
	cmd = set_in_cmd(cmd, args, s);

	if (!cmd)
		return(NULL);
	cmd = clean_args(cmd);
	// free(args[0]);
	// free(args[1]);
	// free(args[2]);
	// free(args);
	return (cmd);
}