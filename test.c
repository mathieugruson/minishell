/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:21 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/14 20:58:23 by mgruson          ###   ########.fr       */
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

les argv se convertissent directement, sauf que tu n'auras pas de argc, que des char.
Il faut donc split. Convertir ce qui peut etre converti, notamment les variables environnement (fait).
Il faut mtn l inserer ds un tout, gerer les leaks et.

Etape : split, regarder s'il y a des variables environnements pr les transformer, il faudra voir si on ameliore en mettant des categories
pour chacun : command, option, etc.



*/

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((s1[i] != '\0') && (i < n)) || ((s2[i] != '\0') && (i < n)))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

char *ft_replace_str(char **envp, int i)
{
	int j = 0;
	int len = 0;
	int	k = 0;
	char *new_var;
	
	printf("c1 : %s\n", envp[i]);
	while(envp[i][j] != '=')
		j++;
	j++;
	len = strlen(envp[i]) - j;
	new_var = malloc(sizeof(char) * (len + 1));
	new_var[len] = 0;
	while(envp[i][j])
		new_var[k++] = envp[i][j++];
	return (new_var);
}

void handle_environment_variables(char **argv, char **envp)
{
	int i = 0;
	int j = 0;
	int k = 1;
	char *str;
	int len = 0;
	char *new;
	while(argv[i])
	{
		// write(1, &argv[i][0], 1);
		if (argv[i][0] == '$' && ft_isalpha(argv[i][1]))
		{
			len = strlen(argv[i]);
			str = malloc(len);
			str[len] = 0;
			while(argv[i][k])
			{
				str[j++] = argv[i][k++];
			}
			printf("t : %s\n", str);
		}
		i++;
	}
	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(str, envp[i], strlen(str)) == 0)
		{	
			printf("%s\n", envp[i]);
			new = ft_replace_str(envp, i);
		}
		i++;
	}
	printf("final : %s\n", new);
	return(new);
}

int	main(int argc, char **argv, char **envp)
{
	char *str[2];
	str[0] = "TEST";
	str[1] = "$USER";
	// printf("test : %s\n", str[1]);
	handle_environment_variables(str, envp);
	return (0);
}