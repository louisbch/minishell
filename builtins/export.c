/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:37:09 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 10:42:03 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

int	is_replacing(t_env *new, t_env **my_env)
{
	t_env	*tmp;

	tmp = *my_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, new->name))
		{
			free(tmp->value);
			tmp->value = strdup(new->value);
			free_env(new);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

bool	is_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
	{
		ft_putstr_fd(" export: `=': not a valid identifier\n", 2);
		return (false);
	}
	if (is_space(arg[i]))
		return (false);
	while (arg[++i])
	{
		if (is_space(arg[i]))
			return (false);
		if (arg[i] == '=')
			return (true);
	}
	return (false);
}

int	export_one(char *args, t_env **my_env)
{
	t_env	*exported;

	if (!args)
		return (0);
	if (only_number(args))
		return (1);
	if (!is_export(args))
		return (1);
	exported = new_env(args);
	if (!exported)
		return (1);
	if (is_replacing(exported, my_env))
		return (0);
	add_env_back(my_env, exported);
	return (0);
}

int	export(char **args, t_env **my_env)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (args[++i])
		res += export_one(args[i], my_env);
	if (res)
		return (1);
	return (0);
}
