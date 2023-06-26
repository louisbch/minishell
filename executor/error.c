/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:36:30 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/16 14:35:13 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_no_file(int fd, char *name)
{
	if (fd == -1)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_signal.val = 1;
		return (1);
	}
	return (0);
}

void	ft_error_cmd(char *cmd)
{
	ft_putstr_fd("Command not found : ", 2);
	ft_putstr_fd(cmd, 2);
	write(1, "\n", 2);
}

void	ft_free_strs(char *str, char **strs)
{
	int	i;

	i = 0;
	if (str)
		free(str);
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}
