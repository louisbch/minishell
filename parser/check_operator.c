/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:49:34 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/16 15:09:15 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_op_len(char *line, t_token *token)
{
	int	res;

	res = check_in(line, token);
	if (res)
		return (res);
	res = check_out(line, token);
	if (res)
		return (res);
	res = check_pipe(line, token);
	if (res)
		return (res);
	return (0);
}

int	check_in(char *line, t_token *token)
{
	int	i;

	i = 0;
	while (line[i] == '<')
		i++;
	if (i > 2)
	{
		printf("parse error near '<'\n");
		token->error = 1;
	}
	return (i);
}

int	check_out(char *line, t_token *token)
{
	int	i;

	i = 0;
	while (line[i] == '>')
		i++;
	if (i > 2)
	{
		printf("parse error near '>'\n");
		token->error = 1;
	}
	return (i);
}

int	check_pipe(char *line, t_token *token)
{
	int	i;

	i = 0;
	while (line[i] == '|')
		i++;
	if (i > 1)
	{
		printf("parse error near '|'\n");
		token->error = 1;
	}
	return (i);
}
