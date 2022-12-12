/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:15:04 by chillion          #+#    #+#             */
/*   Updated: 2022/12/10 13:38:53 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (nmemb != 0 && (nmemb * size / nmemb) != size)
	{
		return (NULL);
	}
	dest = malloc(nmemb * size);
	if (dest == NULL)
	{
		return (NULL);
	}
	ft_bzero(dest, nmemb * size);
	return (dest);
}
