/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:40:20 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/16 15:53:34 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset_one(char *cmd, t_env **my_env)
{
	t_env	*tmp;
	t_env	*previous;

	tmp = *my_env;
	if (!ft_strcmp(cmd, (*my_env)->name))
	{
		*my_env = (*my_env)->next;
		free_env(tmp);
	}
	while (tmp)
	{
		if (!ft_strcmp(cmd, tmp->name))
		{
			previous->next = tmp->next;
			free_env(tmp);
		}
		previous = tmp;
		tmp = tmp->next;
	}
}

void	unset(char **args, t_env **my_env)
{
	int	i;

	i = 0;
	while (args[++i])
		unset_one(args[i], my_env);
}
