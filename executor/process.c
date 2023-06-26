/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:51:01 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 12:21:22 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	dup_fd(int i, t_global *global, t_mred *mred, t_cmd *cmd)
{
	if (i < global->cmd - 1)
	{
		if (dup2(global->fd[i][1], STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Error dup2\n", 2);
			return (1);
		}
	}
	if (i != 0)
	{
		if (mred->fd_in == -2)
			heredoc(mred->delim, 1);
		else if (dup2(global->fd[i - 1][0], STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Error dup2\n", 2);
			return (1);
		}
	}
	if (ft_close_fd(global))
		return (1);
	return (0);
}

void	child_process(t_global *global, t_cmd *cmd, int i, t_mred *mred)
{
	if (dup_fd(i, global, mred, cmd))
		exit(EXIT_FAILURE);
	if (ft_redir(mred, global, cmd))
		exit(EXIT_FAILURE);
	if (cmd->builts && !cmd->cmd)
	{
		g_signal.val = exec_builtins(cmd, global);
		exit(g_signal.val);
	}
	if (!cmd->cmd_path && cmd->cmd && mred->fd_in != -2)
	{
		if (global->path)
		{
			write(2, "command not found : ", 20);
			ft_putstr_fd(cmd->cmd, 2);
			write(2, "\n", 1);
		}
		exit(127);
	}
	if (execve(cmd->cmd_path, cmd->args, global->envp) == -1)
		exit(EXIT_FAILURE);
}

int	ft_create_pipe(int **fd, t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->cmd - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd("Error pipe\n", 2);
			return (1);
		}
	}
	return (0);
}

int	**create_fd_and_pipe(t_global *global)
{
	int	**fd;
	int	i;

	i = -1;
	fd = malloc(sizeof(int *) * (global->cmd - 1));
	if (!fd)
		return (0);
	while (++i < global->cmd - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (0);
	}
	if (ft_create_pipe(fd, global) || !fd)
		return (0);
	return (fd);
}

int	ft_process(pid_t *pid, t_global *global, t_cmd *cmd, t_mred *mred)
{
	int	**fd;
	int	i;

	i = -1;
	global->fd = create_fd_and_pipe(global);
	if (!global->fd)
		return (1);
	if (!is_heredoc(cmd, global, mred))
		return (0);
	while (++i < global->cmd)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(EXIT_FAILURE);
		if (pid[i] == 0)
			child_process(global, &cmd[i], i, &mred[i]);
	}
	ft_close_fd(global);
	wait_child(pid, global);
	return (0);
}
