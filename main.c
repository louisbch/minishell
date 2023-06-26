/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:32:41 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 11:37:31 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	d_exit(t_env **my_env, int out, t_global *global)
{
	free_myenv(my_env);
	rl_clear_history();
	exit(out);
}

void	minishell(t_env **my_env, t_global *global)
{
	t_token	**token;
	char	*line;

	while (1)
	{
		line = readline("$>   ");
		if (!line)
			d_exit(my_env, g_signal.val, global);
		if (line[0] != '\0')
		{
			token = parse(line, my_env);
			if (token)
			{
				do_execution(global, my_env, token);
			}
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_env		**my_env;
	t_global	global;

	(void)av;
	g_signal.exit = -2;
	if (ac != 1)
		return (0);
	set_signals();
	my_env = init_env(envp);
	if (!my_env)
		return (1);
	set_pwd(&global);
	minishell(my_env, &global);
	return (0);
}
