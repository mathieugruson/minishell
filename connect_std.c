/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_std.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:52 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/30 12:13:39 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir(char **redir)
{
    int i;

    i = 0;
    while(redir[i])
    {
        if (strcmp(redir[i], "<<") == 0)
            return (1);       
        if (strcmp(redir[i], "<") == 0)
            return (1);
        if (ft_strcmp(redir[i], ">>") == 0)
            return (1);
        if (ft_strcmp(redir[i], ">") == 0)
            return (1);         
        i++;
    }
    return (0);
}

// int is_redir_out(char **redir)
// {
//     int i;

//     i = 0;
//     while(redir[i])
//     {
//         if (ft_strcmp(redir[i], ">>") == 0)
//             return (1);
//         if (ft_strcmp(redir[i], ">") == 0)
//             return (1);
//         i++;
//     }
//     return (0);
// }

void    out(char *redir_file, char c)
{
    int fd;
    
    if (c == 'D')
    {
        fd = open(redir_file, O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (fd == -1)
            return ;
        dup2(fd, 0);		
		close(fd);
    }
    if (c == 'S')
    {
    fd = open(redir_file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd == -1)
        return ;
    dup2(fd, 0);		
	close(fd);
    }   
}

void    in(char *redir_file, char c, t_m *var)
{
    int fd;

    if (c == 'D')
    {
        // SIGNAL a rajouter et voir comment faire
		(*var).comp = ft_strjoin(redir_file, "\n");
		(*var).heredoc_status = 1;
		ft_trunc_init_fd(".tmpheredoc5", &fd);
		ft_heredoc_fd(var, 1, 1);
        dup2(fd, 0);		
		close(fd);        
    }
    if (c == 'S')
    {
        fd = open(redir_file, O_RDONLY, 0777);
        if (fd == -1)
        {    
            write(2, "ERROR\n", 6);
            exit (-2);
        }
        dup2(fd, 0);		
		close(fd);
    }   
}

void    get_std_redir(char **redir, t_m *var)
{
    int i;

    i = 0;
    while(redir[i])
    {
        if (strcmp(redir[i], "<<") == 0)
            in(redir[i + 1], 'D', var);
        if (strcmp(redir[i], "<") == 0)
            in(redir[i + 1], 'S', var);
        if (strcmp(redir[i], ">>") == 0)
            out(redir[i + 1], 'D');
        if (strcmp(redir[i], ">") == 0)
            out(redir[i + 1], 'S');                 
        i = i + 2;
    }
}

// int connect_stdout(char **redir, int pipex)
// {
//     int i;
//     int fd;

//     fd = pipex;
//     i = 0;
//     while(redir[i])
//     {
//         if (strcmp(redir[i], ">>") == 0)
//         {
//             fd = out(redir[i + 1], 'D');        
//         } 
//         if (strcmp(redir[i], ">") == 0)
//         {
//             fd = out(redir[i + 1], 'S');         
//         }
//         i = i + 2;
//     }
//     return (fd);   
// }

