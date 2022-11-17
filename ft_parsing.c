/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/17 13:00:10 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_minishell
// {
// 	int		simple_tab;
// 	int		double_tab;
// 	int		triple_tab;
// }	t_pointer;

static int	ft_tab(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	printf("ft_tan c1\n");
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{	
			count++;
		}	
		while (s[i] && s[i] != c && s[i] != '|' && s[i] != '>' && s[i] != '<')
		{
			if (s[i] && s[i] == 34)
			{
				i++;
				while(s[i] != 34)
					i++;
				i++;
			}
			printf("char c : %c\n", s[i]);
			if (s[i] && s[i] == 39)
			{
				i++;
				while(s[i] != 39)
					i++;
				i++;
			}
			printf("char c2 : %c\n", s[i]);
			if (s[i] != 0 && s[i] != 34 && s[i] != 39 && s[i] != '|' && s[i] != '>' && s[i] != '<')	
				i++;
		}
		if ((s[i] == '>' && s[i+1] == '>') || (s[i] == '<' && s[i+1] == '<'))
		{
			count++;
			i = i + 2;
		}
		if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			count++;
			i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	printf("nombre de double pointeur : %d\n", count);
	return (count);
}

static char	**ft_free_tab(char **s, int t)
{
	while (t >= 0)
	{
		free(s[t]);
		s[t] = NULL;
		t--;
	}
	return (s);
}

static char	**ft_taboftab(char const *s, char c, char **s1)
{
	int	i;
	int	count;
	int	t;

	i = 0;
	count = 0;
	t = 0;
	while (s[i] && s[i] != '\n')
	{
		while (s[i] && s[i] == c)
			i++;
		if ((s[i] == '>' && s[i+1] == '>') || (s[i] == '<' && s[i+1] == '<'))
		{
			printf("count string pipe : 2\n");
			s1[t] = (char *)ft_calloc((2 + 1), sizeof(char));
			if (!s1[t++])
			{
				s1 = ft_free_tab(s1, t);
				return (s1);
			}
			i = i + 2;			
		}			
		if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			// printf("count string pipe : 1\n");
			s1[t] = (char *)ft_calloc((1 + 1), sizeof(char));
			if (!s1[t++])
			{
				s1 = ft_free_tab(s1, t);
				return (s1);
			}
			i++;			
		}
		while (s[i] && s[i] != c && s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\n')
		{
			if (s[i] && s[i] == 34)
			{
				i++;
				count++;
				while(s[i] != 34)
				{	
					i++;
					count++;
				}
				// count--;	
			}
			if (s[i] && s[i] == 39)
			{
				i++;
				count++;
				while(s[i] != 39)
				{
					count++;	
					i++;
				}
				// count--;
			}
			if (s[i] != 0 && s[i] != '\n')			
			{
				// printf("i %i", i);
				i++;
				count++;
				// printf("t\n");
			}
		}
		// printf("l\n");
		if (count != 0)
		{
			printf("count string : %i\n", count);
			s1[t] = (char *)ft_calloc((count + 1), sizeof(char));
			if (!s1[t++])
			{
				s1 = ft_free_tab(s1, t);
				return (s1);
			}
			count = 0;
		}
	}
	return (s1);
}

static char	**fill_args(char const *s, char c, char **s1)
{
	int	l;
	int	i;
	int	t;

	l = 0;
	i = 0;
	t = 0;
	printf("c1\n");
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

char **malloc_args(char *s, char c)
{
	char	**args;
	
	args = NULL;
	args = (char **)ft_calloc((ft_tab(s, c) + 1), sizeof(char *));
	if (!args)
		return (NULL);
	args = ft_taboftab(s, c, args);
	if (!*args)
	{
		return (args);
	}
	return (args);
}

int	we_are_in_quote(char *str, int i)
{
	int	quote;

	quote = 0;
	while (i >= 0)
	{
		printf("waiq : str[i] = %c\n", str[i]);
		if (str[i] == 34 || str[i] == 39)
			quote++;
		i--;
	}
	printf("quote : %i\n", quote);	
	return(quote % 2);
}

int	ft_triple_pointer_len(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && !we_are_in_quote(s, i))
		{
			count++;	
			i = i + 2;
		}
		i++;
	}
	count = count + (count + 1) ;
	// printf("triple pointer len : %i\n", count);
	return (count);
	
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
			counter++;	
			i++;
		}
		// printf("c2\n");
		if (counter > 0)
		{
			test[j] = malloc(sizeof(char *) * (counter + 1));
			printf("counter test : %i\n", counter);
			test[j][counter] = NULL;
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
			// printf("counter test : %i\n", counter);
			test[j] = malloc(sizeof(char *) * (counter + 1));
			test[j][counter] = NULL;
			j++;
			counter = 0;
		}
	}
	i = 0;
	j = 0;
	// printf("c4\n");
	while(args[i])
	{
		while (args[i] && (args[i][0] != '|' && args[i][0] != '<' && args[i][0] != '>'))
			test[j][k++] = args[i++];
		// ft_putdoubletab(test[j]);
		j++;
		k = 0;
		while (args[i] && (args[i][0] == '|' || args[i][0] == '<' || args[i][0] == '>'))
			test[j][k++] = args[i++];
		if (k > 0)
			// ft_putdoubletab(test[j]);

		j++;
		k = 0;
	}
	// printf("c4\n");
	return (test);
}

char	**ft_parsing(char *s)
{
	char	***test;
	char	**args;
	int		triple_pointer_len = 0;


	(void)triple_pointer_len;
	if (!s)
		return (NULL);
	if (!is_cmdline_valid(s))
		return (NULL);
	// printf("c1\n");	
	args = malloc_args(s, ' ');
	if (!*args)
		return (NULL);	
	args = fill_args(s, ' ', args);
	printf("c1bis\n");	
	triple_pointer_len = ft_triple_pointer_len(s);
	printf("tpl : %i\n", triple_pointer_len);	
	test = malloc(sizeof(char **) * triple_pointer_len + 1);
	if (!test)
		return (NULL);
	test[triple_pointer_len] = NULL;
	printf("before test :\n");
	ft_putdoubletab(args);	
	test = fill_test(test, args);
	printf("triple tab before cleaning :\n");
	ft_puttripletab(test);	
	test = clean_quote(test);
	printf("triple tab after cleaning :\n");
	ft_puttripletab(test);
	return (args);
}