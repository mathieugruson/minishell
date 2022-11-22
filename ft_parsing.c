/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:09:33 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/22 20:37:42 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp_minishell(char *s1, char *s2, int n, int i)
{
	int j;

	j = 0;
	while (((s1[i] != '\0') && (i < n)) || ((s2[j] != '\0') && (i < n)))
	{
		if (s1[i] != s2[j])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		}
		i++;
		j++;
	}
	if (s2[j] != '=')
		return (1);
	return (0);
}

int ft_strlenenv(char *envp)
{
	int i;
	int len;
	int size;
	
	i = 0;
	len = 0;
	size = ft_strlen(envp);
	while(envp[i])
	{
		if (envp[i] && envp[i] == '=')
		{
			while (envp[i] && i <= size)
			{
				len++;
				i++;
			}
		}
		i++;		
	}
	return (len - 1);
}

char *get_env(char *env,  char *envp)
{
	int i;
	int size;
	int j;
	
	j = 0;
	i = 0;
	size = ft_strlen(envp);
	while(envp[i])
	{
		if (envp[i] && envp[i] == '=')
		{
			i++;
			while (envp[i] && i <= size)
			{
				env[j++] = envp[i++];
			}
		}
		i++;		
	}
	return (env);
}

char *get_new_args(char *str, int end, int start, char *envp)
{
	t_index i;
	char *newstring;
	char *env;
	
	i = initialize_index();
	i.count = end - start;
	// printf("stlren str : %li, i.count : %i, strlen env : %i\n", ft_strlen(str), i.count, ft_strlenenv(envp));
	i.len = ft_strlen(str) - (i.count + 1) + ft_strlenenv(envp);
	env = ft_calloc(sizeof(char), (ft_strlenenv(envp) + 1));
	env = get_env(env, envp);
	// printf("env : %s\n", env);
	// printf("i.len : %i\n", i.len);
	(void)i;
	newstring = ft_calloc(sizeof(char), (i.len + 1));
	while (str[i.i1])
	{
		// printf("c1\n");
		while(str[i.i1] && i.i1 != (start - 1))
			newstring[i.i2++] = str[i.i1++];
		// printf("c1bis new : %c, str : %c\n",newstring[i.i2], str[i.i1]);
		while(env[i.i3])
			newstring[i.i2++] = env[i.i3++];
		// printf("c1ter\n");
		i.i1 = i.i1 + i.count + 1;
		while(str[i.i1])
			newstring[i.i2++] = str[i.i1++];  	
		// printf("c1quater\n");
	}
	// printf("new : %s\n", newstring);
	free(env);
	free(str);
	return (newstring);
}

char *get_new_args2(char *str, int end, int start)
{
	t_index i;
	char *newstring;
	
	i = initialize_index();
	i.count = end - start;
	// printf("stlren str : %li, i.count : %i\n", ft_strlen(str), i.count);
	i.len = ft_strlen(str) - (i.count + 1);
	(void)i;
	newstring = ft_calloc(sizeof(char), (i.len + 1));
	while (str[i.i1])
	{
		// printf("c1\n");
		while(str[i.i1] != '$')
			newstring[i.i2++] = str[i.i1++];
		// printf("c1bis\n");
		i.i1 = i.i1 + i.count + 1;
		// printf("c1ter %i\n", i.i1);
		while(str[i.i1])
			newstring[i.i2++] = str[i.i1++];  	
		// printf("c1quater\n");
	}
	// printf("new : %s\n", newstring);
	free(str);
	return (newstring);
}

int is_in_env(char **envp, char *str, int end, int start)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if (ft_strncmp_minishell(str, envp[i], end, start) == 0)
			return (i);
		i++;
	}
	return (0);		
}

char	*is_env_var(char *str, char **envp)
{
	t_index i;
	
	i = initialize_index();
	while (str[i.i])
	{
		if (str[i.i] == '$' && ft_isalpha(str[i.i+1]) > 0 && !is_in_simple_quote(str, i.i))
		{						
			i.start = i.i + 1;
			i.i++;
			while(str[i.i] && str[i.i] != ' ' && str[i.i] != 39 && str[i.i] != 34 && str[i.i] != '$')
		 	{	
				i.i++;
			}
			i.end = i.i;
			// printf("end : %c\n", str[i.i]);
			i.j = is_in_env(envp, str, i.end, i.start);
			if (i.j > 0)
			{
				str = get_new_args(str, i.end, i.start, envp[i.j]);
				i.i = i.start - 2 + ft_strlenenv(envp[i.j]);
				// printf("c4 i.i %i\n", i.i);
			}
			else 
			{
				str = get_new_args2(str, i.end, i.start);
				i.i = i.start - 2;
				// printf("c4bis i.i %i\n", i.i);
			}
			i.j = 0;
		}
		i.i++;		
	}
	// printf("c1\n");
	return (str);
}

char **get_env_var(char **args, char **envp)
{
	t_index i;

	i = initialize_index();
	while(args[i.i])
	{
		args[i.i] = is_env_var(args[i.i], envp);
		// printf("args after change : %s\n", args[i.i]);
		i.i++;	
	}
	return (args);
}

char	***ft_parsing(char *s, char **envp)
{
	char	***cmd;
	char	**args;

	if (!s || s[0] == '\n')
		return (NULL);
	if (!is_cmdline_valid(s))
		return (NULL);
	args = get_args(s, ' ');
	if (!args)
		return (NULL);	
	args = get_env_var(args, envp);
	cmd = NULL;
	cmd = set_in_cmd(cmd, args, s);
	if (!cmd)
		return(NULL);
	cmd = clean_args(cmd);
	return (cmd);
}