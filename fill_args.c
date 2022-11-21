/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 20:14:02 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_args(char *s, char c, char **s1)
{
	t_index i;

	i = initialize_index();
	while (s[i.i] && s[i.i] !='\n')
	{
		while (s[i.i] && s[i.i] == c)
			i.i++;
		i.l = 0;
		while ((s[i.i] == '>' || s[i.i] == '<' || s[i.i] == '|'))
		{	
			s1[i.t][i.l++] = s[i.i++];
		}
		if (i.l != 0 && i.t++ > -1)
			i.l = 0;	
		while (s[i.i] && ((s[i.i] != c && s[i.i] != '|' && s[i.i] != '<' && s[i.i] != '>' && s[i.i] != '\n') || is_in_quote(s, i.i)))
		{
			s1[i.t][i.l++] = s[i.i++];
		}
		if (i.l != 0 && i.t++ > -1)
			i.l = 0;	
	}
	s1[i.t] = NULL;
	return (s1);
}

char **malloc_double_pointer(char **tab, int count)
{
	tab = malloc(sizeof(char *) * (count + 1));
	tab[count] = NULL;
	return (tab);
}

char ***malloc_test(char ***test, char **args)
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

char ***fill_test(char ***test, char **args)
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
