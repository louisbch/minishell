/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:18:42 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/03 14:59:04 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(t_data *data)
{
	char	*line;
	while (1)
	{
		data->line_readline = readline("$>   ");
		if (data->line_readline[0] != '\0')
		{
			parse(data->line_readline);
			// execute();
		}
		free(data->line_readline);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		return (0);
	// data.env = env;
	minishell(&data);
	//free tout
	// line = readline("$>");
	return (0);
}
