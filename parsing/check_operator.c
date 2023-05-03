/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:49:34 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/02 11:55:14 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_in(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '<')
		i++;
	return (i);
}

int	check_out(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '>')
		i++;
	return (i);
}

int	check_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '|')
		i++;
	return (i);
}
