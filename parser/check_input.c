/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:48:18 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/16 18:05:52 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_token_multiple_operator(t_token **token)
{
	t_token	*tmp;
	int		verif;

	tmp = *token;
	if (tmp->type > 1 && !tmp->next)
	{
		printf("parse error near '%s'\n", tmp->token_s);
		return (1);
	}
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type > 1 && (tmp->previous->type > 1 || !tmp->next))
		{
			if (!tmp->next)
				printf("parse error near '\\n'\n");
			else
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
			if (tmp->previous->type >= 1 || !tmp->next)
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

bool	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
			i++;
	if (i == ft_strlen(line))
		return (true);
	return (false);
}
