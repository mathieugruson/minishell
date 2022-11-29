/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_std.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:29:52 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/29 15:53:09 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir_in(char **redir)
{
    int i;

    i = 0;
    while(redir[i])
    {
        if (strcmp(redir[i], "<<") == 0)
            return (1);       
        if (strcmp(redir[i], "<") == 0)
            return (1);         
        i++;
    }
    return (0);
}

int is_redir_out(char **redir)
{
    int i;

    i = 0;
    while(redir[i])
    {
        if (ft_strcmp(redir[i], ">>") == 0)
            return (1);
        if (ft_strcmp(redir[i], ">") == 0)
            return (1);
        i++;
    }
    return (0);
}

int out(char *redir_file, char c)
{
    static int i = 0;
    static int fd;
       
    if (i++ > 0)
        close(fd);
    if (c == 'D')
    {
    fd = open(redir_file, O_CREAT | O_WRONLY | O_APPEND, 0777);
    if (fd == -1)
        return (-2);
    }
    if (c == 'S')
    {
    fd = open(redir_file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd == -1)
        return (-2);
    }   
    return (fd);
}

int in(char *redir_file, char c)
{
    static int i = 0;
    static int fd;
       
    if (i++ > 0)
        close(fd);
    if (c == 'D')
    {
        fd = open(redir_file, O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (fd == -1)
        {    
            printf("%s : No such file or directory\n", redir_file);
            exit (-2);
        }
    }
    if (c == 'S')
    {
        fd = open(redir_file, O_RDONLY, 0777);
        if (fd == -1)
        {    
            printf("%s : No such file or directory\n", redir_file);
            exit (-2);
        }
    }   
    return (fd);
}

int connect_stdin(char **redir, int pipex)
{
    int i;
    int fd;

    fd = pipex;
    i = 0;
    while(redir[i])
    {
        if (strcmp(redir[i], "<<") == 0)
        {
            fd = in(redir[i + 1], 'D');
        }
        if (strcmp(redir[i], "<") == 0)
        {
            fd = in(redir[i + 1], 'S');
        }
        i = i + 2;
    }
    return (fd);  
}

int connect_stdout(char **redir, int pipex)
{
    int i;
    int fd;

    fd = pipex;
    i = 0;
    while(redir[i])
    {
        if (strcmp(redir[i], ">>") == 0)
        {
            fd = out(redir[i + 1], 'D');        
        } 
        if (strcmp(redir[i], ">") == 0)
        {
            fd = out(redir[i + 1], 'S');         
        }
        i = i + 2;
    }
    return (fd);   
}

