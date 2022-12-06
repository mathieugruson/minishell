/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:47 by chillion          #+#    #+#             */
/*   Updated: 2022/12/06 14:58:25 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int has_quote(char *str)
{
	int i;
	int s;
	int d;
	
	i = 0;
	s = 0;
	d = 0;
	while(str[i])
	{
		if (str[i] == 34)
			d++;
		else if (str[i] == 39)
			s++;
		i++;
	}
	if (d + s >= 2)
		return (1);
	return (0);
}

char	*get_env_var_heredoc(char *str, char **envp, t_index i, t_m *var)
{
	(void)var; // cela sera utile pour mettre a jour le statut
	while (str[i.i])
	{
		if (str[i.i] == '$' && ft_isalpha(str[i.i + 1]) > 0)
		{						
			i.start = ++i.i;
			while (str[i.i] && str[i.i] != ' '\
			&& str[i.i] != 39 && str[i.i] != 34 && str[i.i] != '$' && str[i.i] != '\n')
				i.end = ++i.i;
			i.j = is_in_env(envp, str, i.end, i.start);
			if (i.j > -1)
			{
				str = add_good_env(str, i.end, i.start, envp[i.j]);
				i.i = i.start - 2;
			}
			else
			{
				str = remove_wrong_env(str, i.end, i.start);
				i.i = i.start - 2;
			}
			i.j = 0;
		}
		if (str[i.i] == '$' && str[i.i + 1] == '?'
		&& !is_in_simple_quote(str, i.i))
		{
			str = add_status(str, (i.i + 2), (i.i + 1), "2"); // "2" a remplacer par la variable status
			i.i = i.i - 1 + ft_intlen(2);
		}	
		i.i++;
	}
	return (str);
}

void	ft_heredoc_fd(t_m *var, int n, int j)
{
	char	*str;
	t_index	i;
	int		quote;

	quote = !has_quote(var->comp);
	i = initialize_index();
	// signal(SIGINT, SIG_DFL);
	// signal(SIGINT, handle_sigint_2);
	signal(SIGQUIT, SIG_IGN);
	while (n > 0)
	{
		str = readline(">");
		if (!str)
		{
			write(2, "warning: don't find end-of-file (wanted `", 42);
			ft_putstr_fd((*var).comp, 2);
			write(2, "')\n", 4);
			return ;
		}
		if (ft_strcmp(clear_quote((*var).comp), str) == 0)
			break ;
		printf("cmp : %s\n", (*var).comp);
		if (quote == 1)
			str = get_env_var_heredoc(str, var->env, i, var);
		write((*var).fdin, str, ft_strlen(str));
		write((*var).fdin, "\n", 2);
		free(str);
		j++;
	}
	free (str);
	return (ft_cleanheredoc_fd(NULL, NULL, (*var).comp, (*var).fdin));
}
