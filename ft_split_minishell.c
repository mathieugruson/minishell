/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/15 19:24:51 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
/*

comment :
pour l'instant il gere bien les parentheses. Il faura voir son 
comportement lorsque 


*/


/* utils */
 
char	*ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		*(char *)s++ = '\0';
		i++;
	}
	return ((char *)s);
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*tab;

	if (nmeb && ((nmeb * size / nmeb) != size))
		return (NULL);
	tab = malloc(nmeb * size);
	if (!tab)
		return (NULL);
	ft_bzero((char *)tab, size * nmeb);
	return ((char *)tab);
}

 /* split */
 
static int	ft_tab(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
		{
			if (s[i] && s[i] == 34)
			{
				i++;
				while(s[i] != 34)
					i++;
			}
			if (s[i] && s[i] == 39)
			{
				i++;
				while(s[i] != 39)
					i++;
			}
			if (s[i] != 0)			
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static char	**ft_free(char **s, int t)
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
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (s[i] && s[i] == 34)
			{
				i++;
				while(s[i] != 34)
				{	
					i++;
					count++;
				}
				count--;	
			}
			if (s[i] && s[i] == 39)
			{
				i++;
				while(s[i] != 39)
				{
					count++;	
					i++;
				}
				count--;
			}
			if (s[i] != 0)			
			{
				i++;
				count++;
			}
		}
		// printf("count : %d\n", count);
		if (count != 0)
		{
			s1[t] = (char *)ft_calloc((count + 1), sizeof(char));
			if (!s1[t++])
			{
				s1 = ft_free(s1, t);
				return (s1);
			}
		}
		count = 0;
	}
	return (s1);
}

static char	**ft_fill(char const *s, char c, char **s1)
{
	int	l;
	int	i;
	int	t;

	l = 0;
	i = 0;
	t = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (s[i] && s[i] == 34)
			{
				i++;
				while(s[i] != 34)
					s1[t][l++] = s[i++];
				if (s[i])
					i++;
			}
			if (s[i] && s[i] == 39)
			{
				i++;
				while(s[i] != 39)
					s1[t][l++] = s[i++];
				if (s[1])
					i++;
			}
			if (s[i] != c)
				s1[t][l++] = s[i++];
		}	
		if (s1[t])
			s1[t++][l] = '\0';
		l = 0;
	}
	s1[t] = NULL;
	return (s1);
}

void	ft_puttab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	printf("resultat :\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}	
}

char	**ft_split(char const *s)
{
	char	**s1;
	char 	c;

	c = ' ';
	if (!s)
		return (NULL);
	s1 = (char **)ft_calloc((ft_tab(s, c) + 1), sizeof(char *));
	if (!s1)
		return (NULL);
	s1 = ft_taboftab(s, c, s1);
	if (!*s1)
	{
		return (s1);
	}
	s1 = ft_fill(s, c, s1);
	ft_puttab(s1);
	return (s1);
}

int main(int argc, char **argv)
{
	// printf("argc : %s\n", argv[1]);
	ft_split(argv[1]);
	return (0);
}