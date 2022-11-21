/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 13:48:14 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int we_are_in_quote(char *str, int i)
{
	int j = 0;

	while(str[j] && j < i)
	{
		if (str[j] && str[j] == 34 && j < i)
		{	
			j++;
			while(str[j] && str[j] != 34)
				j++;
			// printf("1 waiq s[j] : %c  j : %i\n", str[j], j);	
			if (str[j] != 0 && j > i)
			{
				// printf("1 in quote str[j] %c\n", str[j]);
				return (1);
			}
		}
		if (str[j] && str[j] == 39 && j < i)
		{	
			j++;
			while(str[j] && str[j] != 39)
				j++;
			// printf("2 waiq s[j] : %c  j : %i\n", str[j], j);	
			if (str[j] != 0 && j > i)
			{
				// printf("2 in quote str[j] %c\n", str[j]);
				return (1);
			}
		}
		j++;
	}
	// printf("not in quote\n");
	return (0);
}


int	double_pointer_nbr(char *s, char c) // ft_tab
{
	int	i;
	int	count;
	int k;
	
	k = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		while ((s[i] && (((s[i] != c && s[i] != '|' && s[i] != '>' && s[i] != '<')) || we_are_in_quote(s, i))))
		{
			if (k++ == 0)
			{
				count++;
			}
			// printf("1 s[i] : %c  i : %i\n", s[i], i);	
			i++;
			// printf("1bis s[i] : %c  i : %i\n", s[i], i);	
		}
		// printf("c2\n");
		k = 0;
		while (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			if (k++ == 0)
			{
				count++;
			}
			// printf("2 s[i] : %c\n", s[i]);
			i++;
		}
		k = 0;
		while (s[i] && s[i] == c)
			i++;
	}
	printf("double pointeur cree: %i\n", count);
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

char *malloc_simple_pointer(int count, int t, char **s1)
{
	s1[t] = (char *)ft_calloc((count + 1), sizeof(char));
	if (!s1[t])
	{
		s1 = ft_free_tab(s1, t);
		return (s1[t]);
	}
	return (s1[t]);
}

char	**simple_pointer_nbr(char *s, char c, char **s1)
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
		while (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			count++;
			i++;	
		}
		if (count != 0)
		{	
			s1[t] = malloc_simple_pointer(count, t, s1);
			printf("t : %i, count %i\n", t, count);
			t++;
			count = 0;			
		}
		while (s[i] && ((s[i] != c && s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '\n') || we_are_in_quote(s, i)))
		{
			count++;
			i++;
		}
		// printf("l\n");
		if (count != 0)
		{
			printf("t : %i, count %i\n", t, count);
			s1[t] = malloc_simple_pointer(count, t, s1);
			t++;
			count = 0;
		}
	}
	return (s1);
}

char **malloc_args(char *s, char c)
{
	char	**args;
	
	args = NULL;
	args = (char **)ft_calloc((double_pointer_nbr(s, c) + 1), sizeof(char *));
	if (!args)
		return (NULL);
	args = simple_pointer_nbr(s, c, args);
	if (!*args)
	{
		return (args);
	}
	return (args);
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

char	***ft_parsing(char *s)
{
	char	***test;
	char	**args;
	int		triple_pointer_len = 0;


	(void)triple_pointer_len;
	if (!s || s[0] == '\n')
		return (NULL);
	// printf("c0\n");
	if (!is_cmdline_valid(s))
		return (NULL);
	// printf("c1\n");	
	args = malloc_args(s, ' ');
	if (!*args)
		return (NULL);	
	args = fill_args(s, ' ', args);
	// printf("c1bis\n");	
	triple_pointer_len = ft_triple_pointer_len(s);
	// printf("tpl : %i\n", triple_pointer_len);	
	test = malloc(sizeof(char **) * triple_pointer_len + 1);
	if (!test)
		return (NULL);
	test[triple_pointer_len] = NULL;
	// printf("before test :\n");
	// ft_putdoubletab(args);
	// write(1, "c2\n", 3);	
	test = fill_test(test, args);
	// printf("triple tab before cleaning :\n");
	// ft_puttripletab(test);	
	// printf("c10\n");
	test = clean_quote(test);
	// test = get_env_var(test);
	// printf("triple tab after cleaning :\n");
	// ft_puttripletab(test);
	return (test);
}