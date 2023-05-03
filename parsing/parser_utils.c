/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:26:09 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/02 12:57:11 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_quote(char c)
{
	int	i;

	i = 0;
	if (c == 34)
		return (1);
	if (c == 39)
		return (2);
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

// void	calloc_line(t_data *data)
// {
// 	int	i;
// 	int	quote;
// 	int	nb_operator;

// 	quote = 0;
// 	nb_operator = 0;
// 	i = 0;
// 	while (data->line_readline[i])
// 	{
// 		if (is_operator(data->line_readline[i]))
// 			nb_operator++;
// 		quote = is_quote(data->line_readline[i]);
// 		i++;
// 		while (quote && data->line_readline[i])
// 		{
// 			if (is_quote(data->line_readline[i]) == quote)
// 				quote = 0;
// 			i++;
// 		}
// 	}
// 	data->line_with_space = ft_calloc((ft_strlen(data->line_readline) + 2 * \
// 	nb_operator + 1), sizeof(char));
// }

// void	better_line(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	int	quote;

// 	quote = 0;
// 	i = 0;
// 	j = 0;
// 	while (data->line_readline[i])
// 	{
// 		data->line_with_space[j] = data->line_readline[i];
// 		quote = 0;
// 		if (is_operator(data->line_readline[i]))
// 		{
			
// 		}
// 		quote = is_quote(data->line_readline[i]);
// 		while (quote && data->line_readline[i])
// 		{
// 			data->line_with_space[i] = data->line_readline[i];
// 			i++;
// 			if (is_quote(data->line_readline[i]) == quote)
// 			{
// 				data->line_with_space[i] = data->line_readline[i];
// 				break;
// 			}
// 		}
// 	}
// }
