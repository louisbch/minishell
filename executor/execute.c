/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:35:58 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 13:00:14 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type > 0)
			break ;
		token = token->next;
		count++;
	}
	return (count);
}

int	is_heredoc(t_cmd *cmd, t_global *global, t_mred *mred)
{
	if (!cmd[0].builts && !cmd[0].cmd_path && global->cmd == 1)
	{
		if (mred[0].delim && mred->fd_in == -2)
		{
			heredoc(mred[0].delim, 0);
			return (0);
		}
	}
	return (1);
}

int	execute(t_cmd *cmd, t_global *global, t_mred *mred)
{
	pid_t	*pid;

	pid = malloc(sizeof(pid_t) * global->cmd);
	if (!pid)
		return (-1);
	ft_process(pid, global, cmd, mred);
	free(pid);
	return (0);
}

void	read_line(char *line, char *stash, char *str, int *fd)
{	
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, str))
			break ;
		stash = ft_strjoin(stash, line);
		stash = ft_strjoin(stash, "\n");
		if (!stash)
			return ;
		free(line);
	}
	if (line)
		free(line);
	write(fd[1], stash, ft_strlen(stash));
	free(stash);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}
