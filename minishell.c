

#include "minishell.h"

void	ft_history_init_fd(char *file, int *fd)
{
	int	t;

	(void)t;
	(*fd) = open(file, O_RDONLY | O_RDWR | O_APPEND);
	if (*fd == -1)
	{
		t = unlink(file);
		(*fd) = open(file, O_RDONLY | O_RDWR | O_CREAT, 0644);
	}
}

void	write_first_c(char *buffer, char *str)
{
	buffer[0] = '\0';
	str[0] = '\0';
}

void	ft_init_commands_history(t_m *var)
{
	char *str;

	str = readline("minishell>");
	if (str)
	{
		ft_history_init_fd(".history", &(*var).h_fd);
		write((*var).h_fd, str, ft_strlen(str));
		(*var).args_line = ft_strdup(str);
	}
}

void	ft_print_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("SPLIT[%d]=%s]\n", i, str[i]);
		i++;
	}
	ft_printf("-----------------\n");
}

void	ft_print_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_env(t_m *var, char **envp)
{
	int i;
	if (!envp)
	{
		(*var).env = (char **)malloc(sizeof(char *) * 1);
		if (!(*var).env)
			return (-1);
		(*var).env[0] = (char *)malloc(sizeof(char) * 1);
		if (!(*var).env[0])
			return (free((*var).env), -1);
		(*var).env[0][0] = '\0';
		return (1);
	}
	i = 0;
	while (envp[i])
		i++;
	(*var).env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*var).env)
		return (-1);
	(*var).env[i] = 0;
	if (!(*var).env)
		return (-1);
	i = 0;
	while (envp[i])
	{
		(*var).env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (0);
}

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	t_m	var;
	char ***args;

	signal(SIGINT, handle_sigint); /* ctrl + c  affiche un nouveau prompt */
	signal(SIGQUIT, SIG_IGN); /* ctrl + \  ne fait rien */
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (ft_printf("Error : Wrong Number of arguments\n"), 1);
	if (ft_env(&var, envp) == -1)
		return (ft_printf("Error : Malloc for keep env fail\n"), 1);
	// ft_print_env(var.env);
	ft_init_commands_history(&var);
	ft_printf("Command is :%s\n", var.args_line);
	args = ft_parsing(var.args_line, envp);
	ft_puttripletab(args);
	free_tripletab(args);
	free(var.args_line);
	ft_free_split(var.env);
	return (0);
}
