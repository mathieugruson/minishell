/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:21 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/14 19:44:45 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void handle_environment_variables(char **argv, char **envp)
{
	int i = 0;
	int y = 0;
	char *str;
	int len = 0;
	
	while(argv[i])
	{
		if (argv[i][0] == '$' && (argv[i][1] >= 'A' && argv[i][1] <= 'Z' \
		||  argv[i][1] >= 'a' && argv[i][1] <= 'z'))
			len = strlen(argv[i]);
			str = malloc(sizeof(char) * len);
			str[len] = 0;		
			while(argv[i][y])
			{
				str[y] = argv[i][y + 1];
				y++;
			}
		i++;
	}
	printf("%s\n", str);
	// while(envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
}

int	main(int argc, char **argv, char **envp)
{
	handle_environment_variables(argv, envp);
	return (0);
}