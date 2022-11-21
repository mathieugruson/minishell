/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 19:57:26 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_pointer_nbr(char *s, char c)
{
	t_index i;

	i = initialize_index();
	while (s[i.i])
	{
		while ((s[i.i] && (((s[i.i] != c && s[i.i] != '|' && s[i.i] != '>' && s[i.i] != '<')) || is_in_quote(s, i.i))))
		{
			if (i.k++ == 0)
				i.count++;
			i.i++;
		}
		i.k = 0;
		while (s[i.i] == '>' || s[i.i] == '<' || s[i.i] == '|')
		{
			if (i.k++ == 0)
				i.count++;
			i.i++;
		}
		i.k = 0;
		while (s[i.i] && s[i.i] == c)
			i.i++;
	}
	return (i.count);
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
	t_index i;

	i = initialize_index();
	while (s[i.i] && s[i.i] != '\n')
	{
		while (s[i.i] && s[i.i] == c)
			i.i++;
		while ((s[i.i] == '>' || s[i.i] == '<' || s[i.i] == '|') && i.count++ > -1)
			i.i++;	
		if (i.count != 0)
		{	
			s1[i.t] = malloc_simple_pointer(i.count, i.t, s1);
			i.t++;
			i.count = 0;			
		}
		while (s[i.i] && ((s[i.i] != c && s[i.i] != '|' && s[i.i] != '<' && s[i.i] != '>' && s[i.i] != '\n') || is_in_quote(s, i.i)) && i.count++ > -1)
			i.i++;
		if (i.count != 0)
		{
			s1[i.t] = malloc_simple_pointer(i.count, i.t, s1);
			i.t++;
			i.count = 0;
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
	test = malloc_test(test, args);	
	test = fill_test(test, args);
	// printf("triple tab before cleaning :\n");
	// ft_puttripletab(test);	
	// printf("c10\n");
	test = clean_args(test);
	// test = get_env_var(test);
	// printf("triple tab after cleaning :\n");
	// ft_puttripletab(test);
	return (test);
}