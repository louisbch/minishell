/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:18:42 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/11 12:47:47 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	minishell(t_env **env)
{
	char	*line;

	while (1)
	{
		line = readline("$>   ");
		if (line[0] != '\0')
		{
			parse(line);
			// execute();
		}
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	**env;

	(void)av;
	if (ac != 1)
		return (0);
	env = init_env(envp);
	minishell(env);
	//free tout
	// line = readline("$>");
	return (0);
}
