/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:41:20 by mgruson           #+#    #+#             */
/*   Updated: 2022/12/08 14:59:27 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Subject : Reproduction of cd function
It handles :
- cd par des chemins relatifs (cd .., cd dir_after)
- cd par chemin absolu

*/

int	find_env_name_line(char *name, char **env)
{
	int i;

	i = 0;
	while(env[i] && ft_strncmp(name, env[i], ft_strlen(name)) != 0)
	{
		i++;
	}
	return (i);	
}

int	export_env(char *name, char *word, t_m *var)
{
	int line;
	
	line = find_env_name_line(name, var->env);
	var->env[line] = ft_strjoin(name, word);
	return(0);
}

char *import_user(char *name, t_m *var)
{
	int line;
	
	line = find_env_name_line(name, var->env);
	return(&var->env[line][5]);
}

int ft_cd(char **cmd, int i, t_m *var)
{
	char	*path;
	char	*newpath;
	int		len;
		
	path = NULL;
	newpath = NULL;
	printf("c0\n");
	path = getcwd(path, 0);
	printf("c0bis\n");	
	len = ft_tablen(cmd);
	printf("c0ter len : %i\n", len);	
	if (len == 1 || (cmd[1] && cmd[1][0] == '~' && !cmd[2]))
	{
		printf("c2\n");
		newpath = import_user("HOME=", var);
		printf("c3\n");
		if (chdir(newpath) != 0) // update user
			return (1);
		return (0);
	}
	else if (len > 2)
		return (write(2, "cd: too many arguments\n", 23), 130);
	else if (cmd[1][0] != '/')
	{
		path = ft_strjoin_free(path, "/");
		path = ft_strjoin_free(path, cmd[i]);
		if (chdir(path) != 0)
			printf("cd: %s No such file or directory\n", cmd[i]);
	}
	else 
	{
		if (chdir(cmd[1]) != 0)
			printf("cd: %s No such file or directory\n", cmd[i]);
	}
	newpath = getcwd(newpath, 0);
	export_env("PWD=", newpath, var);
	return (0);
}