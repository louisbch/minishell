/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:18:42 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/12 10:19:32 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	minishell(t_env **my_env)
{
	char	*line;
	t_token	**token;

	while (1)
	{
		line = readline("$>   ");
		if (line[0] != '\0')
		{
			token = parse(line, my_env);
			if (token)
			{
				// execute();
				g_signal = 0;
				free_token(token);
			}
			else
				g_signal = 1;
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_env	**my_env;

	(void)av;
	if (ac != 1)
		return (0);
	my_env = init_env(envp);
	minishell(my_env);
	//free tout
	return (0);
}
