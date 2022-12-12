

#include "minishell.h"

int exit_status;

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


void	handle_sigint_3(int sig)
{
	exit_status += sig;
	if (sig == 2)
	{
		write(1, "\n", 2);
		signal(SIGINT, SIG_IGN);
		exit(130);
	}
}

void	handle_sigint_2(int sig)
{
	exit_status += sig;
	if (sig == 2)
	{
		exit_status = 130;
		write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_sigint_1(int sig)
{
	exit_status += sig;
	if (sig == SIGINT)
	{
		exit_status = 130;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_init_heredoc(t_m *var)
{
	pid_t	pid;
	
	var->h_status = open(".heredocstatus", O_RDWR | O_CREAT, 0644);
	close(var->h_status);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	(pid) = fork();
	if ((pid) == -1)
		return (write(2, "Error with fork\n", 17), ft_fork_fail(var));
	if ((pid) == 0)
	{
		if (ft_strcmplen(var->redir, "<<") > 0)
			handle_heredoc_child(var);
		unlink(".heredocstatus");
		free_child_heredoc(var);
		exit(1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, 0, 0);
		exit_status = 130;
		var->h_status = open(".heredocstatus", O_RDWR);
		ft_signal(1);
	}
	return ;
}

void	ft_daddy(t_m *var, int *pid, int nbcmd)
{
	int	i;

	i = 0;
	ft_signal(2);
	while (i < nbcmd && nbcmd != 0 && var->h_status == -1)
	{
		if (is_env_builtin(var->cmd[0]) && var->tablen == 1)
			break;
		waitpid(pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			exit_status = 128 + WTERMSIG(exit_status);
		i++;
	}
	ft_signal(1);
	if (var->h_status > 2)
	{
		close(var->h_status);
		var->h_status = 0;
		unlink(".heredocstatus");
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

int	ft_exec(t_m *var, char ***args)
{
	var->exec = 0;
	var->tabexec = 0;
	var->h_status = -1;
	if (!args)
		return (0);
	var->pid = (int *)malloc(sizeof(int) * (var->tablen + 1));
	if (!var->pid)
		return (free_parent(var), 1);
	var->pid[var->tablen] = 0;
	if (ft_strcmplen(var->redir, "<<") > 0)
		ft_init_heredoc(var);
	ft_init_all_pipe(var);
	if (var->tablen >= 1 && var->h_status == -1)
	{
		while ((var->exec) < var->tablen)
		{
			ft_do_pipe_fork(var, args[var->exec][0], args[var->exec], &var->pid[var->exec]);
			var->exec++;
		}
	}
	if (var->h_status  != -1)
		ft_unlink_all(var, 0);
	ft_daddy(var, var->pid, var->tablen);
	return (0);
}

int	ft_puttriplelen(char ***test, t_m *var)
{
	var->tablen = 0;
	if (!test || !*test)
		return (var->tablen);
	if (!*test[0])
		return (var->tablen);
	while(test[var->tablen] != NULL)
		var->tablen++;
	return (var->tablen);
}

int	main(int argc, char **argv, char **envp)
{
	t_m	var;

	ft_signal(1);
	(void)argv;
	if (argc != 1)
		return (ft_printf("Error : Wrong Number of arguments\n"), 1);
	initialize_var(&var);
	if (ft_create_env(&var, envp) == -1)
		return (ft_printf("Error : Malloc for keep env fail\n"), 1);
	while (1)
	{
		var.args_line = NULL;
		ft_init_commands_history(&var);
		if (!var.args_line)
			return (free_doubletab(var.env), rl_clear_history(), write(2, "exit\n", 6), 0);
		if (!will_return_nothing(var.args_line) && is_cmdline_valid(var.args_line))
		{
			ft_parsing(&var, var.env, &var.cmd, &var.redir);
			ft_puttriplelen(var.cmd, &var);
			ft_exec(&var, var.cmd);
			update_last_env(&var);
			free_parent(&var);
		}
		free(var.args_line);
	}
	return (0);
}
