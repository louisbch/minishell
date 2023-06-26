/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:35:07 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/15 16:59:51 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	echo_cmp(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
		return (false);
	if (cmd->args[1][0] != '-')
		return (false);
	while (cmd->args[1][i] == 'n')
		i++;
	if (cmd->args[1][i] == '\0' && i > 1)
		return (true);
	return (false);
}

void	echo(t_cmd *cmd)
{
	int	i;
	int	n;

	i = 1;
	if (echo_cmp(cmd))
		n = 1;
	else
		n = 0;
	while (cmd->args[i + n])
	{
		printf("%s", cmd->args[i + n]);
		i++;
		if (cmd->args[i + n])
			printf(" ");
	}
	if (!n)
		printf("\n");
}
