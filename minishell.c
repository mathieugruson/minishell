

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

void	ft_init_commands_history(t_m *var)
{
	char *str;

	str = NULL;
	while (1)
	{
		// if (str)
		// 	free(str);
		ft_signal(1);
		str = readline("minishell>");
		if (!str)
			break ;
		else if (ft_strlen(str))
		{
			add_history(str);
			ft_history_init_fd(".history", &(*var).h_fd);
			write((*var).h_fd, str, ft_strlen(str));
			write((*var).h_fd, "\n", 1);
			close((*var).h_fd);
			(*var).args_line = ft_strdup(str);
			free(str);
			str = NULL;
			break ;
		}
		// else if (!ft_strlen(str))
		// {
		// 	if (*str)
		// 		free(str);
		// }
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

void	handle_sigint_2(int sig)
{
	int status = 0;

	(void)status;
	status += sig;
	if (sig == 2)
	{
		status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_sigint_1(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		exit (1);
	}
}

void	ft_daddy(t_m *var, int *pid, int nbcmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	(void)var;
	while (i < nbcmd && nbcmd != 0)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		i++;
	}
}

int	ft_init_pipe(t_m *var, int i)
{
	var->pipex[i] = (int *)malloc(sizeof(int) * (2));
	if (!var->pipex[i])
		return (2);
	if (pipe(var->pipex[i]) == -1)
		return (write(2, "Error with pipe\n", 17), ft_fork_fail(var), 2);
	return (0);
}



int	ft_init_all_pipe(t_m *var)
{
	int	i;

	i = 0;
	var->pipex = (int **)malloc(sizeof(int *) * (var->tablen + 1));
	if (!var->pipex)
		return (printf("malloc error\n"), 2);
	var->pipex[var->tablen] = NULL;
	while (i < var->tablen)
	{
		if (ft_init_pipe(var, i) == 2)
			return (2);
		i++;
	}
	return (0);
}

void	ft_free_inttab(int **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_exec(t_m *var, char ***args)
{
	var->exec = 0;
	var->tabexec = 0;
	var->pid = (int *)malloc(sizeof(int) * (var->tablen + 1));
	if (!var->pid)
		return (printf("malloc error\n"), 1);
	var->pid[var->tablen] = 0;
	ft_init_all_pipe(var);
	// if (var->tablen == 1)
	// 	ft_do_fork(var, args[0][0], args[0], &var->pid[0]);
	if (var->tablen >= 1)
	{
		while ((var->exec) < var->tablen)
		{
			ft_do_pipe_fork(var, args[var->exec][0], args[var->exec], &var->pid[var->exec]);
			var->exec++;
		}
	}
	ft_free_inttab(var->pipex);
	ft_daddy(var, var->pid, var->tablen);
	return (0);
}

int	ft_puttriplelen(char ***test, t_m *var)
{
	var->tablen = 0;

	if (!test)
		return (var->tablen);
	while(test[var->tablen])
		var->tablen++;
	return (var->tablen);
}

int export_last_args(t_m *var)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(var->cmd[i])
	{
		j = 0;
		while(var->cmd[i][j])
			j++;
		i++;
	}
	printf("var : %s\n", var->cmd[i - 1][j - 1]);
	export_env("_=", var->cmd[i - 1][j - 1], var);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_m	var;

	ft_signal(1);
	(void)argv;
	(void)envp;
	if (argc != 1)
		return (ft_printf("Error : Wrong Number of arguments\n"), 1);
	if (ft_create_env(&var, envp) == -1)
		return (ft_printf("Error : Malloc for keep env fail\n"), 1);
	while (1)
	{
		var.args_line = NULL;
		ft_init_commands_history(&var);
		if (!var.args_line)
			return (ft_free_split(var.env), rl_clear_history(), printf("exit\n"), 0);
		if (ft_parsing(&var, var.env, &var.cmd, &var.redir) == 2)
			return (2);
		free(var.args_line);
		ft_puttriplelen(var.cmd, &var);
		ft_exec(&var, var.cmd);
		export_last_args(&var);
		free_all(&var);
	}
	return (0);
}
