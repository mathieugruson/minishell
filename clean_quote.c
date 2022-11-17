/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:10:48 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/17 12:52:04 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *remove_quote(char *str, int quote, int i)
{
	// printf("i : %i\n", i);
	int ibis = 0;
	i--;
	while(str[i] != quote)
		i--;
	ibis = i;
	printf("i2 : %i\n", i);
	while (str[i])
	{
		if (str[i] == quote)
		{	
			while (str[i])
			{
				str[i] = str[i+1];
				i++;
			}
		}
		i++;
	}
	i = ibis;
	while (str[i])
	{
		if (str[i] == quote)
		{	
			while (str[i])
			{	
				str[i] = str[i+1];
				i++;
			}
		}
		i++;
	}
	// printf(" str : %s\n", str);
	return (str);
}

char *clear_quote(char *str)
{
	int i = 0;
	int dq = 0;
	int sq = 0;
	int	j = 0;
	
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			j++;		
		i++;
	}
	if (j == 0)
		return (str);
	i = 0;
	printf("c1\n");
	// printf("str[i]: %c", str[i]);
	while(str[i])
	{
		if (str[i] == 34)	
		{
			dq++;
			// printf("dq : %i, sq : %i\n", dq, sq);
			if (dq == 2 && (sq == 2 || sq == 0))
			{	
				str = remove_quote(str, 34, i);
				dq = 0;
				sq = 0;
				i = i - 2;
				printf("str : %s, i: %i\n", str, i);
			}
		}
		else if (str[i] == 39)
		{
			// printf("c3\n");			
			sq++;
			if (sq == 2 && (dq == 2 || dq == 0))
			{
				str = remove_quote(str, 39, i);
				sq = 0;
				dq = 0;
				i = i - 2;
			}
		}
		i++;
	}
	return (str);
}

char ***clean_quote(char ***test)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(test[i])
	{
		j = 0;
		printf("c4\n");	
		while(test[i][j])
		{
			test[i][j] = clear_quote(test[i][j]);
			j++;
		}
		i++;
	}
	return (test);
}
