/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:36:17 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 12:25:12 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	only_digit(char *s)
{
	int	i;

	i = 0;
	if ((s[i] == '-' || s[i] == '+') && s[1])
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			printf("exit : %s: numeric argument required\n", s);
			return (255);
		}
		i++;
	}
	return (0);
}

bool	one_arg_max(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i != 2)
	{
		printf("exit: too many arguments\n");
		return (false);
	}
	return (true);
}

int	get_exit_code(char *s)
{
	unsigned int	i;

	i = ft_atoi(s);
	i = i << 24;
	i = i >> 24;
	return (i);
}

int	ft_exit(t_global *global, t_cmd *cmd)
{
	int	i;
	int	ex;
	int	dig;

	i = 0;
	if (!cmd->args[1])
	{
		printf("exit\n");
		if (g_signal.val)
			g_signal.exit = g_signal.val;
		else
			g_signal.exit = -1;
		return (0);
	}
	dig = only_digit(cmd->args[1]);
	if (dig)
		return (dig);
	if (!one_arg_max(cmd->args))
		return (1);
	printf("exit\n");
	g_signal.exit = get_exit_code(cmd->args[1]);
	return (0);
}
