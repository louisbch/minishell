/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:48:31 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 16:59:23 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_global(t_global *global, t_env **my_env, t_token *token)
{
	global->envp = list_tab(my_env);
	global->path = get_path(*my_env);
	global->cmd = count_cmd(token);
	global->my_env = my_env;
	return (0);
}

void	read_heredoc_not_alone(char *str, char *line, char *stash, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		read_line(line, stash, str, fd);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	read_heredoc_alone(char *str, char *line)
{
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, str))
			break ;
		free(line);
	}
	if (line)
		free(line);
}

void	heredoc(char *str, int a)
{
	char	*line;
	char	*stash;
	int		fd[2];

	line = ft_calloc(1, 2);
	if (!line)
		return ;
	stash = ft_calloc(1, 2);
	if (!stash)
		return ;
	if (pipe(fd) == -1)
		return ;
	if (!a)
		read_heredoc_alone(str, line);
	else
		read_heredoc_not_alone(str, line, stash, fd);
	if (line)
		free(line);
}
