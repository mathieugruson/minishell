/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:48:30 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 12:43:50 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**fill_args(char *s, char c, char **s1)
{
	int	l;
	int	i;
	int	t;

	l = 0;
	i = 0;
	t = 0;
	// printf("c1\n");
	while (s[i] && s[i] !='\n')
	{
		while (s[i] && s[i] == c && s[i] != '|' && s[i] != '<' && s[i] != '>')
			i++;
		if ((s[i] == '>' && s[i+1] == '>') || (s[i] == '<' && s[i+1] == '<'))
		{
			// t++;
			l = 0;
			s1[t][l++] = s[i++];
			s1[t][l++] = s[i++];
			// printf("string %s\n", s1[t]);
			if (s[i] != c)
				t++;
			l = 0;
		}
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			// t++;
			l = 0;
			// printf("atm %i l %i i %i\n", t, l, i);
			s1[t][l++] = s[i++];
			// printf("string %s\n", s1[t]);
			// printf("c2quater t %i l %i i %i\n", t, l, i);				
			if (s[i] != c)
				t++;
			l = 0;
		}		
		while (s[i] && s[i] != c && s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\n')
		{
			// printf("c2\n");
			if (s[i] && s[i] == 34)
			{
				s1[t][l++] = s[i++];
				while(s[i] != 34)
					s1[t][l++] = s[i++];
				s1[t][l++] = s[i++];
			}
			if (s[i] && s[i] == 39)
			{
				s1[t][l++] = s[i++];
				while(s[i] != 39)
					s1[t][l++] = s[i++];
				s1[t][l++] = s[i++];
			}
			// printf("c3 %c\n", s[i]);
			if (s[i] && s[i] != c && s[i] != '\n' && s[i] != 34 && s[i] != 39 && s[i] != '|' && s[i] != '<' && s[i] != '>' )
			{
				// printf("atm : t %i l %i i %i\n", t, l, i);
				s1[t][l++] = s[i++];
				// printf("atm 1 : %s\n", s1[t]);
			}	
			// printf("string %s\n", s1[t]);
		}
		t++;	
		l = 0;
	}
	// printf("c4\n");
	s1[t] = NULL;
	// ft_putdoubletab(s1);
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
