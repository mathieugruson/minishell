/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:50:29 by chillion          #+#    #+#             */
/*   Updated: 2022/12/05 16:13:44 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_itoa(int n)
{
	int			i;
	long int	nb;
	char		*str;

	nb = n;
	i = ft_nb_size(nb, "0123456789");
	str = (char *)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		str[i] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	return (str);
}
/*
int main()
{
	int i;

	i = -555465;
	printf("%s", ft_itoa(i));
}
*/