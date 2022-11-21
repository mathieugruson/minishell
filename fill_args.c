/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 16:50:02 by mgruson          ###   ########.fr       */
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
		while (s[i.i] && ((s[i.i] != c && s[i.i] != '|' && s[i.i] != '<' && s[i.i] != '>' && s[i.i] != '\n') || we_are_in_quote(s, i.i)))
		{
			s1[i.t][i.l++] = s[i.i++];
		}
		if (i.l != 0 && i.t++ > -1)
			i.l = 0;	
	}
	s1[i.t] = NULL;
	return (s1);
}

char ***fill_test(char ***test, char **args)
{
	int	i; 
	int	j;
	int k;
	int counter;
	
	i = 0;
	k = 0;
	j = 0;
	counter = 0;
	// printf("c1\n");
	while(args[i])
	{
		while (args[i] && (args[i][0] != '|' && args[i][0] != '<' && args[i][0] != '>'))
		{
			// printf("s : %s\n", args[i]);	
			// printf("c3 i : %i\n", i);
			counter++;	
			i++;
		}
		// printf("args[i] : %s, i : %i\n", args[i], i);
		// printf("c2\n");
		if (counter > 0)
		{
			test[j] = malloc(sizeof(char *) * (counter + 1));
			// printf("counter test : %i\n", counter);
			test[j][counter] = NULL;
			// printf(" test[j][counter] : %s\n", test[j][counter]);
			j++;
			counter = 0;
		}
		// printf("c2bis\n");
		while (args[i] && (args[i][0] == '|' || args[i][0] == '<' || args[i][0] == '>'))
		{		
			counter++;
			i++;
		}
		// printf("c2ter\n");
		if (counter > 0)
		{
			// printf("counter test 2 : %i\n", counter);
			test[j] = malloc(sizeof(char *) * (counter + 1));
			test[j][counter] = NULL;
			j++;
			counter = 0;
		}
	}
	i = 0;
	j = 0;
	k = 0;
	// printf("c4\n");
	while(args[i])
	{
		while (args[i] != NULL && (args[i][0] != '|' && args[i][0] != '<' && args[i][0] != '>'))
		{	
			// printf("j %i k %i i %i\n", j, k, i);
			// printf("s : %s\n", args[i]);	
			test[j][k] = args[i];
			k++;
			i++;
		}
		// printf("c4bis1\n");
		// ft_putdoubletab(test[j]);
		j++;
		k = 0;
		while (args[i] && (args[i][0] == '|' || args[i][0] == '<' || args[i][0] == '>'))
			test[j][k++] = args[i++];
		// if (k > 0)
			// ft_putdoubletab(test[j]);
		j++;
		k = 0;
	}
	// printf("c4ter\n");
	return (test);
}
