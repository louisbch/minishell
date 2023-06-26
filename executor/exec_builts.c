/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:26:43 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 16:00:54 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	only_number(char *args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (args[i] && ft_isdigit(args[i]) && args[i] != '=')
		i++;
	while (args[len] && args[len] != '=')
		len++;
	if (len != i)
		return (false);
	printf("export: '%s' not a valid identifier\n", args);
	return (true);
}

int	exec_builtins(t_cmd *cmd, t_global *global)
{
	int	res;

	res = 0;
	if (!ft_strcmp(cmd->builts, "export"))
		res = export(cmd->args, global->my_env);
	if (!ft_strcmp(cmd->builts, "cd"))
		res = cd(cmd, global);
	if (!ft_strcmp(cmd->builts, "unset"))
		unset(cmd->args, global->my_env);
	if (!ft_strcmp(cmd->builts, "echo"))
		echo(cmd);
	if (!ft_strcmp(cmd->builts, "env"))
		res = env(cmd->args, global->my_env);
	if (!ft_strcmp(cmd->builts, "pwd"))
		pwd(global);
	if (!ft_strcmp(cmd->builts, "exit"))
		res = ft_exit(global, cmd);
	return (res);
}
