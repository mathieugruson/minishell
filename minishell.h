
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

typedef struct s_index
{
	int i;
	int i1;
	int i2;
	int i3;
	int j;
	int j1;
	int j2;
	int j3;
	int start;
	int end;
	int count;
	int k;
	int t;
	int l;
	int counter;	
}	t_index;

/* fill_args.c*/

char	**fill_args(char *s, char c, char **s1);
char ***fill_test(char ***test, char **args);

/* ft_parsing.c */

char	***ft_parsing(char *s);
int	we_are_in_quote(char *str, int i);
int	double_pointer_nbr(char *s, char c);
char *malloc_simple_pointer(int count, int t, char **s1);
char	**simple_pointer_nbr(char *s, char c, char **s1);
char **malloc_args(char *s, char c);
int	ft_triple_pointer_len(char *s);

/* mathieu_utils.c */

void	ft_putdoubletab(char **tab);
void	ft_puttripletab(char ***test);

/* is_cmdline_valid.c */

int is_cmdline_valid(char *str);

/* clean_quote.c */

char ***clean_args(char ***test);

/* replace_env_var.c */

void handle_environment_variables(char **argv, char **envp);

/* we_are_in_quote.c  */

int we_are_in_quote(char *str, int i);

/* initialize_index.c */

t_index initialize_index();

#endif