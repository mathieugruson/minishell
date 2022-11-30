/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:46:03 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/30 16:51:28 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_heredoc(char ***redir)
{
    int i;
    int j;
    
    i = 0;
    while(redir[i])
    {
        j = 0;
        while(redir[i][j])
        {
            if (strcmp(redir[i][j], "<<") == 0)
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int ft_heredoclen(char ***redir)
{
    int i;
    int j;
    int k;

    k = 0;
    i = 0;
    while(redir[i])
    {
        j = 0;
        while(redir[i][j])
        {
            if (strcmp(redir[i][j], "<<") == 0)
                k++;
            j++;
        }
        i++;
    }
    return (k);   
}

char **malloc_heredoc(t_m *var)
{
    int heredoc_len;
    
    heredoc_len = ft_heredoclen(var->redir);
    var->heredoc = ft_calloc(sizeof(char *), (heredoc_len + 1));
    return (var->heredoc);
}

char **get_heredoc_filename(char **heredoc, int i)
{
    char *str;

    str = ft_strjoin(".heredoc", ft_itoa(i));
    heredoc[i] = ft_calloc(sizeof(char), (ft_strlenint(str) + ft_intlen(i) + 1));
    // printf("str : %s\n", str);
    ft_strlcpy(heredoc[i], str, (ft_strlenint(str) + 1));
    // printf("str : %s\n", heredoc[i]);
    return (heredoc);
}

void get_heredoc(char *str, t_m *var)
{
    static int i = 0;
    
    (*var).comp = ft_strjoin(str, "\n");
    var->heredoc = get_heredoc_filename(var->heredoc, i);
    
	(*var).heredoc_status = 1;
    // printf("str : %s\n", var->heredoc[i]);
	ft_trunc_init_fd(var->heredoc[i], &(*var).fdin);
	ft_heredoc_fd(var, 1, 1);
    close((*var).fdin);
    i++;   
}

void handle_heredoc(t_m *var)
{
    int i;
    int j;
    int k;

    k = 0;
    i = 0;
    var->heredoc = malloc_heredoc(var);
    while(var->redir[i])
    {
        j = 0;
        while(var->redir[i][j])
        {
            if (strcmp(var->redir[i][j], "<<") == 0)
            {    
                printf("c1 i: %i j: %i, redir[i]: %s\n", i, j, var->redir[i][j]);
                get_heredoc(var->redir[i][j+1], var);
                var->redir[i][j][1] = '\0';
                var->redir[i][j+1] = var->heredoc[k];
                k++;
            }    
            j++;
        }
        i++;
    }
}