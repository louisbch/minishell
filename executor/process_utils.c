/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:24:39 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 12:19:36 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_cmd(t_token *token)
{
	int	count;

	count = 1;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

void	wait_child(pid_t *id, t_global *global)
{
	int	i;
	int	ret;

	i = 0;
	while (i < global->cmd)
	{
		waitpid(id[i], &ret, 0);
		i++;
		if (WIFEXITED(ret))
			g_signal.val = WEXITSTATUS(ret);
	}
}

void	free_fd(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->cmd - 1)
	{
		if (global->fd[i])
		{
			free(global->fd[i]);
			global->fd[i] = NULL;
		}
		i++;
	}
	if (global->fd)
	{
		free(global->fd);
		global->fd = NULL;
	}
}

int	ft_close_fd(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->cmd - 1)
	{
		if (close(global->fd[i][0]) == -1)
		{
			ft_putstr_fd("Error close\n", 2);
			return (1);
		}
		if (close(global->fd[i][1]) == -1)
		{
			ft_putstr_fd("Error close\n", 2);
			return (1);
		}
		i++;
	}
	free_fd(global);
	return (0);
}
