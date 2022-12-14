/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/14 18:48:24 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_quote(char *str)
{
	str = clear_quote(str);
	if (!str[0])
		return (1);
	return (0);
}

int	is_empty_env_var(char *str, t_m *var)
{
	int	i;
	int	line ;

	i = 0;
	if (str[i] == '$' && ((ft_isalpha(str[i + 1]) > 0) || \
		str[i + 1] == '_') && !is_in_simple_quote(str, i))
	{
		line = find_env_name_line(&str[1], var->env);
		if (line == ft_tablen(var->env))
			return (1);
	}
	return (0);
}

int	will_return_nothing(char *str, t_m *var)
{
	int	i;

	i = 0;
	if (str[i] == '\n' && ft_strlen(str) == 0)
		return (1);
	if ((str[i] == ':' || str[i] == '!') && ft_strlen(str) == 1)
		return (1);
	if (is_only_quote(str))
		return (1);
	if (is_empty_env_var(str, var))
		return (1);
	while (str[i] != 0 && str[i] != '\n')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_parsing(t_m *var, char **envp, char ****cmd, char ****redir)
{
	char	**args;

	if (get_args(&args, var->args_line, ' ', var) == 2)
		return (2);
	args = get_env_var(args, envp);
	*cmd = NULL;
	*redir = NULL;
	if (set_in_cmd(args, var) == 2)
		return (2);
	free(args);
	args = NULL;
	*cmd = clean_args(*cmd);
	*redir = clean_args(*redir);
	return (0);
}
