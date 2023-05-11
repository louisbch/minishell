/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:53:03 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/11 14:11:09 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env(t_env **my_env)
{
	t_env	*tmp;

	tmp = *my_env;
	while (tmp)
	{
		printf("%s", tmp->name);
		printf("=%s\n", tmp->value);
		tmp = tmp->next;
	}
}
