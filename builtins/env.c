/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:35:57 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 16:13:22 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmp_builtin_env(t_cmd *cmd, t_token *tmp)
{
	g_signal.val = 0;
	if (!ft_strcmp(str_lower(cmd->args[0]), "env"))
		if (cmd->args[1])
			g_signal.val = 127;
	cmd->builts = tmp->token_s;
}

int	env(char **args, t_env **my_env)
{
	t_env	*tmp;

	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (127);
	}
	tmp = *my_env;
	while (tmp)
	{
		printf("%s", tmp->name);
		printf("=%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
