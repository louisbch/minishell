/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:42:47 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 16:58:42 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_nb_char(int *i, int a)
{
	free(i);
	if (a)
		return (1);
	return (0);
}

int	free_myenv(t_env **my_env)
{
	t_env	*tmp;

	while (*my_env)
	{
		tmp = (*my_env)->next;
		free_env(*my_env);
		*my_env = tmp;
	}
	free(my_env);
	return (1);
}

void	free_token(t_global *global)
{
	t_token	*temp;
	t_token	*token;

	token = global->first;
	while (token)
	{
		temp = (token)->next;
		if ((token)->token_s)
			free ((token)->token_s);
		free(token);
		token = temp;
	}
	token = NULL;
}

void	ft_free_struct(t_cmd *cmd, t_global *global)
{
	int	i;

	i = 0;
	while (i < global->cmd)
	{
		if (cmd[i].args)
		{
			free(cmd[i].args);
			cmd[i].args = NULL;
		}
		if (cmd[i].cmd_path)
		{
			free(cmd[i].cmd_path);
			cmd[i].cmd_path = NULL;
		}
		i++;
	}
}

void	ft_free_all(t_global *global, t_mred *mred, t_cmd *cmd)
{
	free_token(global);
	if (mred)
		free(mred);
	free_tabs(global->envp);
	ft_free_struct(cmd, global);
	if (cmd)
		free(cmd);
	ft_free_path(global);
}
