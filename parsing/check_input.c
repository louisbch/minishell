/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:18:18 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/08 16:04:04 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_token_multiple_operator(t_token **token)
{
	t_token	*tmp;
	int		verif;

	tmp = *token;
	if (tmp->type > 1)
	{
		printf("parse error near '%s'\n", tmp->token_s);
		return (1);
	}
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type > 1 && tmp->previous->type > 1)
		{
			printf("parse error near '%s'\n", tmp->token_s);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_token_pipe(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type == PIPE)
	{
		printf("parse error near '|'\n");
		return (1);
	}
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (tmp->previous->type >= 1)
			{
				printf("parse error near '|'\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_input(t_token **token)
{
	if (check_token_pipe(token))
		return (1);
	if (check_token_multiple_operator(token))
		return (1);
	return (0);
}
