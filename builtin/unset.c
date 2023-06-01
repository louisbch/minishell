/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:29:16 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/01 11:46:04 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

void	unset(char *name, t_env **my_env)
{
	t_env	*tmp;
	t_env	*previous;

	tmp = *my_env;
	if (!ft_strcmp(name, (*my_env)->name))
	{
		*my_env = (*my_env)->next;
		free_env(tmp);
	}
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			previous->next = tmp->next;
			free_env(tmp);
		}
		previous = tmp;
		tmp = tmp->next;
	}
}
