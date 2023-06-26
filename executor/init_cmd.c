/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:17:18 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/21 18:56:44 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	define_builtin_type(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "export"))
		cmd->open = 0;
	else if (!ft_strcmp(cmd->args[0], "cd"))
		cmd->open = 0;
	else if (!ft_strcmp(cmd->args[0], "unset"))
		cmd->open = 0;
	else if (!ft_strcmp(str_lower(cmd->args[0]), "echo"))
		cmd->open = 1;
	else if (!ft_strcmp(str_lower(cmd->args[0]), "env"))
		cmd->open = 1;
	else if (!ft_strcmp(str_lower(cmd->args[0]), "pwd"))
		cmd->open = 1;
	else if (!ft_strcmp(cmd->args[0], "exit"))
		cmd->open = 0;
	else
		cmd->open = -1;
}

int	count_redir(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->type > 1)
			count++;
		if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
	return (count);
}

void	save_first_token(t_global *global, t_token **token)
{
	global->first = *token;
}

void	init_cmd(t_token **token, t_cmd *cmd, t_global *global, t_mred *mred)
{
	int		i;

	i = 0;
	save_first_token(global, token);
	while (i < global->cmd)
	{
		mred[i].error = 0;
		mred[i].fd_in = -1;
		mred[i].fd_out = -1;
		mred[i].delim = NULL;
		mred[i].infile = NULL;
		mred[i].outfile = NULL;
		i++;
	}
	mat_redir(token, mred, global);
	minit_cmd(token, cmd, global);
}
