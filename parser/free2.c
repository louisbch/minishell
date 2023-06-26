/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:02:32 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/23 16:12:32 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_path(t_global *global)
{
	int	i;

	i = 0;
	if (global->path)
	{
		if (global->path[i])
		{
			while (global->path[i])
			{
				free(global->path[i]);
				global->path[i] = NULL;
				i++;
			}
			if (global->path)
			{
				free(global->path);
				global->path = NULL;
			}
		}
	}
}
