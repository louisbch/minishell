/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:05:04 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/21 17:06:47 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	ctrl c ;
void	handle_sigint(int sig)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (pid == -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal.val = 1;
	}
	if (pid == 0)
	{
		g_signal.val = 130;
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (pid == 0)
	{
		g_signal.val = 131;
		ft_putstr_fd("^\\Quit: 3\n", 2);
	}
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
		handle_sigint(sig);
	if (sig == SIGQUIT)
		handle_sigquit(sig);
}

void	set_signals(void)
{
	struct termios	term;

	tcgetattr(fileno(stdout), &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(fileno(stdout), TCSANOW, &term);
	signal(SIGINT, &handle_sig);
	signal(SIGQUIT, &handle_sig);
}
