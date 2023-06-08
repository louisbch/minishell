/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:26:09 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/08 16:02:51 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_token_type(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (!ft_strcmp(tmp->token_s, ">>"))
			tmp->type = APP;
		else if (!ft_strcmp(tmp->token_s, "<<"))
			tmp->type = HERE;
		else if (!ft_strcmp(tmp->token_s, "<"))
			tmp->type = I_FILE;
		else if (!ft_strcmp(tmp->token_s, ">"))
			tmp->type = O_FILE;
		else if (!ft_strcmp(tmp->token_s, "|"))
			tmp->type = PIPE;
		else
			tmp->type = CMD;
		tmp = tmp->next;
	}
}

void	double_link(t_token **token)
{
	t_token	*tmp;
	t_token	*prev;

	prev = NULL;
	tmp = *token;
	while (tmp)
	{
		tmp->previous = prev;
		prev = tmp;
		tmp = tmp->next;
	}
}

int	is_quote(char c)
{
	int	i;

	i = 0;
	if (c == 34)
		return (34);
	if (c == 39)
		return (39);
	return (0);
}

int	is_operator(char c)
{
	int		i;

	i = 0;
	if (c == '|')
		return (1);
	if (c == '<')
		return (2);
	if (c == '>')
		return (3);
	return (0);
}
