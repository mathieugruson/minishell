/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:59:14 by mgruson           #+#    #+#             */
/*   Updated: 2022/11/21 19:18:15 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	int i = 0;

	if (argv[1][i] == 'T' && i++ > -1)
		printf("test\n");
	printf("i : %i\n", i);
}