/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 12:57:02 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_triple_pointer_len(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && !is_in_quote(s, i))
		{
			count++;	
			i = i + 2;
		}
		i++;
	}
	count = count + (count + 1) ;
	printf("triple pointer len : %i\n", count);
	return (count);
	
}

char **malloc_double_pointer(char **tab, int count)
{
	tab = malloc(sizeof(char *) * (count + 1));
	tab[count] = NULL;
	return (tab);
}

char ***malloc_cmd(char ***test, char **args)
{
	t_index i;

	i = initialize_index();
	while(args[i.i])
	{
		while (args[i.i] && (args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>') && i.i++ > -1)
			i.counter++;	
		if (i.counter > 0)
		{
			test[i.j] = malloc_double_pointer(test[i.j], i.counter);
			i.j++;
			i.counter = 0;
		}
		while (args[i.i] && (args[i.i][0] == '|' || args[i.i][0] == '<' || args[i.i][0] == '>') && i.i++ > -1)	
			i.counter++;
		if (i.counter > 0)
		{
			test[i.j] = malloc_double_pointer(test[i.j], i.counter);
			i.j++;
			i.counter = 0;
		}
	}	
	return (test);
}

char ***fill_cmd(char ***test, char **args)
{
	t_index i;

	i = initialize_index();

	i.i = 0;
	i.j = 0;
	i.k = 0;
	while(args[i.i])
	{
		while (args[i.i] != NULL && (args[i.i][0] != '|' && args[i.i][0] != '<' && args[i.i][0] != '>'))
		{	

			test[i.j][i.k] = args[i.i];
			i.k++;
			i.i++;
		}

		i.j++;
		i.k = 0;
		while (args[i.i] && (args[i.i][0] == '|' || args[i.i][0] == '<' || args[i.i][0] == '>'))
			test[i.j][i.k++] = args[i.i++];
		i.j++;
		i.k = 0;
	}
	return (test);
}

char ***set_in_cmd(char ***cmd, char **args, char *s)
{	
	int		triple_pointer_len;
	
	triple_pointer_len = ft_triple_pointer_len(s);
	cmd = malloc(sizeof(char **) * triple_pointer_len + 1);
	if (!cmd)
		return (NULL);
	cmd[triple_pointer_len] = NULL;
	cmd = malloc_cmd(cmd, args);	
	cmd = fill_cmd(cmd, args);
	return (cmd);
}
