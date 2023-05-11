/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:26:09 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/11 12:11:31 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
