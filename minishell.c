
#include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

void	ft_cleanhistory_fd(char *str, char *buffer, int fd)
{
	free(str);
	free(buffer);
	close(fd);
}

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

int	ft_history_end(char *str, int i, t_m *var)
{
	if (str[i] == '\n')
	{
		write((*var).history_fd, str, strlen(str));
		(*var).args_line = ft_strdup(str);
		close((*var).history_fd);
		return (0);
	}
	return (1);
}

void	write_first_c(char *buffer, char *str)
{
	buffer[0] = '\0';
	str[0] = '\0';
}

void	ft_init_commands_history(t_m *var)
{
	char	*buffer;
	char	*str;
	int		j;
	int		n;

	j = 0;
	n = 1;
	ft_history_init_fd(".history", &(*var).history_fd);
	buffer = (char *)malloc(sizeof(char) * 2);
	if (!buffer)
		return ;
	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return ;
	write_first_c(buffer, str);
	while (n > 0)
	{
		n = (read(0, buffer, 1));
		if (n == -1)
			ft_cleanhistory_fd(str, buffer, (*var).history_fd);
		buffer[1] = '\0';
		str = ft_strjoin_free(str, buffer);
		if (!ft_history_end(str, j, var))
			break ;
		j++;
	}
	return (ft_cleanhistory_fd(str, buffer, (*var).history_fd));
}

void	signal_int(int unused)
{
	(void)unused;
	rl_on_new_line();
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_m	var;
	char ***args;

	(void)argv;
	(void)envp;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_int); // mettre une fonction a la place qui donne une autre ligne


	if (argc == 1)
	{
		ft_init_commands_history(&var);
		ft_printf("Command is :%s", var.args_line);
		args = ft_parsing(var.args_line);
		ft_puttripletab(args);
		free_tripletab(args);
		free(var.args_line);
	}
	else
		ft_printf("Error : Wrong Number of arguments\n");
	return (0);
}