
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/wait.h>
# include "libs/libft/includes/libft.h"
# include "libs/libft/includes/ft_printf.h"

typedef struct s_minishell
{
	int		history_fd;
	char	*args_line;
}	t_m;

// typedef struct s_index
// {
// 	int	static static0;
// 	int static static1;
// 	int	start;
// 	int end;
// 	int i;
// 	int i0;
// 	int i1;
// 	int i2;
// 	int i3;
// 	int i4;
// 	int i5;

// } t_index;

/* ft_parsing.c */

char	***ft_parsing(char *s);
int	we_are_in_quote(char *str, int i);

/* mathieu_utils.c */

void	ft_putdoubletab(char **tab);
void	ft_puttripletab(char ***test);

/* is_cmdline_valid.c */

int is_cmdline_valid(char *str);

/* clean_quote.c */

char ***clean_quote(char ***test);

/* replace_env_var.c */

void handle_environment_variables(char **argv, char **envp);

#endif