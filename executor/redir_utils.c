/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:28:07 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/20 15:43:20 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	modif_in(t_token *tmp, t_mred *mred)
{
	tmp = tmp->next;
	if (mred->fd_in != -1 && mred->fd_in != -2)
		close(mred->fd_in);
	mred->fd_in = open(tmp->token_s, O_RDONLY);
	if (ft_no_file(mred->fd_in, tmp->token_s))
		mred->error = 1;
	mred->infile = tmp->token_s;
}

void	modif_out(t_token *tmp, t_mred *mred)
{
	tmp = tmp->next;
	if (mred->fd_out != -1)
		close(mred->fd_out);
	mred->fd_out = open(tmp->token_s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ft_no_file(mred->fd_out, tmp->token_s))
		mred->error = 1;
	mred->outfile = tmp->token_s;
}

void	modif_app(t_token *tmp, t_mred *mred)
{
	tmp = tmp->next;
	if (mred->fd_out != -1)
		close(mred->fd_out);
	mred->fd_out = open(tmp->token_s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ft_no_file(mred->fd_out, tmp->token_s))
		mred->error = 1;
	mred->outfile = tmp->token_s;
}

void	modif_here(t_token *tmp, t_mred *mred)
{
	tmp = tmp->next;
	mred->delim = tmp->token_s;
	if (mred->fd_in != -1)
		close (mred->fd_in);
	mred->fd_in = -2;
}
