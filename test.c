/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:08:08 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/23 16:12:16 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	mat_redir(t_token **token, t_mred *mred, t_global *global)
{
	t_token	*tmp;
	int		j;

	j = 0;
	tmp = *token;
	while (tmp)
	{
		if (tmp->type == I_FILE)
			modif_in(tmp, &mred[j]);
		if (tmp->type == O_FILE)
			modif_out(tmp, &mred[j]);
		if (tmp->type == APP)
			modif_app(tmp, &mred[j]);
		if (tmp->type == HERE)
			modif_here(tmp, &mred[j]);
		if (!tmp)
			return ;
		if (tmp->type == PIPE)
			j++;
		tmp = tmp->next;
	}
}

char	**mcount_args_andmalloc(t_token *token)
{
	int		i;
	t_token	*tmp;
	char	**args;

	i = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type > 1)
		{
			tmp = tmp->next->next;
		}
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	if (!i)
		return (NULL);
	args = malloc(sizeof(char *) * i + 1);
	if (!args)
		return (NULL);
	args[i] = NULL;
	return (args);
}

int	mis_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(str_lower(cmd), "echo"))
		return (1);
	if (!ft_strcmp(str_lower(cmd), "env"))
		return (1);
	if (!ft_strcmp(str_lower(cmd), "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

t_token	*mcreate_cmd(t_token *tmp, t_cmd *cmd, int i, t_global *global)
{
	t_token	*first;

	first = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type > 1)
			tmp = tmp->next->next;
		else
		{
			if (!first)
				first = tmp;
			cmd->args[i] = tmp->token_s;
			tmp = tmp->next;
			i++;
		}
	}
	if (mis_builtins(cmd->args[0]))
		cmp_builtin_env(cmd, first);
	else
	{
		cmd->cmd = first->token_s;
		cmd->cmd_path = join_path(first, global->path, global->my_env);
	}
	return (tmp);
}

void	minit_cmd(t_token **token, t_cmd *cmd, t_global *global)
{
	int		i;
	int		first;
	t_token	*tmp;

	tmp = *token;
	i = -1;
	first = 0;
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->builts = NULL;
	cmd->cmd = NULL;
	while (++i < global->cmd)
	{
		cmd[i].args = mcount_args_andmalloc(tmp);
		if (tmp && tmp->type != PIPE)
		{
			if (cmd[i].args)
			{
				tmp = mcreate_cmd(tmp, &cmd[i], 0, global);
				define_builtin_type(&cmd[i]);
			}
		}
		if (tmp && tmp->type == PIPE)
			tmp = tmp->next;
	}
}
