/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:12:01 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/21 16:38:29 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_in_redir(t_mred *redir, t_global *global, t_cmd *cmd)
{
	if (redir->fd_in == -2 && global->cmd == 1 && \
			!cmd->builts)
		heredoc(redir->delim, 1);
	if (redir->fd_in != -1 && redir->fd_in != -2)
	{
		if (dup2(redir->fd_in, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Error dup2\n", 2);
			return (1);
		}
		if (close(redir->fd_in) == -1)
		{
			ft_putstr_fd("Error close\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_redir(t_mred *mred, t_global *global, t_cmd *cmd)
{
	if (mred->error == 1)
		return (1);
	if (check_in_redir(mred, global, cmd))
		return (1);
	if (mred->fd_out != -1)
	{
		if (dup2(mred->fd_out, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Error dup2\n", 2);
			return (1);
		}
		if (close(mred->fd_out) == -1)
		{
			ft_putstr_fd("Error close\n", 2);
			return (1);
		}
	}
	return (0);
}
