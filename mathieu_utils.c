/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathieu_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:36:40 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/23 15:29:54 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putdoubletab(char **tab)
{
	static int j = 0;
	int	i;

	i = 0;
	if (!tab)
		return ;
	printf("command %i :\n", j++);
	while (tab[i])
	{
		ft_putstr(tab[i]);
		write(1, "\n", 1);
		i++;
	}	
}

void	ft_puttripletab(char ***test)
{
	int i ; 

	i = 0;
	if (!test)
		return ;
	while(test[i])
	{
		ft_putdoubletab(test[i]);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_tablen(char **tab)
{	
	int	y;

	y = 0;
	while (tab[y])
	{
		y++;
	}
	return (y);
}

/* check if of the both double tab are well sorted in the same way */
int ft_tabsort_cmp(char **s1, char **s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i] && strcmp(s1[i], s2[i]) == 0)
		i++;
	printf("s1 : %s\n s2 : %s\n", s1[i], s2[i]);
	return (i);
}

/* check if of the string of the double tab or in the other tab */
int ft_tabunsort_cmp(char **tab1, char **tab2)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	
	while(tab1[i])
	{
		j = 0;
		while (tab2[j])
		{
			if (ft_strcmp(tab1[i], tab2[j]) == 0)
			{
				printf ("i : %i OK\n", i);
			}
			j++;
		}
		i++;
	}
	return(1);
}

void	*ft_memcpy_mathieu(void *dest, void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return ((char *)dest);
}