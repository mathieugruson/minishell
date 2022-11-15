/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:34:48 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/15 16:46:18 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

// char **parsing(char *)
// {
// 	while (str)
// 		while(is_displayable)
// 			i++;
// 		while(is_not_space)
		
// 			if (c = $ ou autre metacharactere)
// 				replace env_var		
// 			if c != "" && c != ''
// 				str= str
// 			if c = ''
// 				c++
// 				while(c != "")
// 					str = str
// 					i++;
// 			if (c = "")
// 				c++
// 				while(c != "")
// 					if (c = $)
// 						replace_env_var	
// 					str = str
// 					i++		
// }

char **parsing(char *)
[
	
]

int main(int argc, char **argv)
{
	int i = 0;
	char c;
	
	while(argv[1][i])
	{
		c = argv[1][i];
		write(1, &c, 1);
		write(1, "\n", 1);
		i++;	
	}
	write(1, "\n", 1);
	return (0);
}