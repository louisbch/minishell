/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:18:06 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/07 17:22:25 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(t_token **token)
{
	t_token	*temp;

	while (*token)
	{
		temp = (*token)->next;
		if ((*token)->token_s)
			free ((*token)->token_s);
		free(*token);
		*token = temp;
	}
	*token = NULL;
	if (token)
		free (token);
}
