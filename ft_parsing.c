/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/01 12:14:56 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(char *s, char **envp, char ****cmd, char ****redir)
{

	char	**args;

	if (!s || s[0] == '\n')
		return (0);
	if (!is_cmdline_valid(s))
		return (2);
	args = get_args(s, ' ');
	if (!args)
		return (0);	
	ft_putdoubletab(args);
	args = get_env_var(args, envp);
	ft_putdoubletab(args);
	*cmd = NULL;
	*redir = NULL;
	set_in_cmd(&*cmd, &*redir, args, s);
	if (!*cmd)
		return (2);
	*cmd = clean_args(*cmd);
	*redir = clean_args(*redir);
	return (0);
}