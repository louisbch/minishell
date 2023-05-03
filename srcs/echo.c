/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:24:26 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/29 10:35:02 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	echo_cmp(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (false);
	if (str[0] != '-')
		return (false);
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0' && i > 1)
		return (true);
	return (false);
}

void	echo(char **s)
{
	int	i;
	int	n;

	i = 0;
	if (echo_cmp(s[0]))
		n = 1;
	else
		n = 0;
	while (s[i + n])
	{
		printf("%s", s[i + n]);
		i++;
		if (s[i + n])
			printf(" ");
	}
	if (!n)
		printf("\n");
}
