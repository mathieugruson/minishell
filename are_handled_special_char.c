/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_handled_special_char.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:19 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/15 15:40:57 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	is_handled_special_char(char *str, int i)
{	
	if (str[i] == ';' || str[i] == '(' || str[i] == ')'\
	||str[i] == '&' || str[i] == 92 || str[i] == '*'\
	|| str[i] == '[' || str[i] == ']' || str[i] == '\t')
		return (0);
	if (str[i] == '?')
	{	
		if (!str[i - 1] && str[i - 1] != '$')
			return (0);
	}
	return (1);	
}
		
int are_handled_special_char(char *str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		if (str[i] == 33)
		{
			i++;
			while (str[i] && str[i] != 33)
				i++;
			if (str[i] == 0)
			{	
				write(1, "Error : close the double quote\n", 31);
				return (0);
			}
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)	
				i++;
			if (str[i] == 0)
			{	
				write(1, "Error : close the simple quote\n", 31);
				return (0);
			}
		}
		if (!is_handled_special_char(str, i))
		{
			write(1, "Error : there are non handled special character\n", 48);
			return (0);	
		}
		i++;
	}
	return (1);	
}