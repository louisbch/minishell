/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:28:02 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/20 14:30:34 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	trunc_length(t_token *token)
{
	int	i;
	int	nb_quote;
	int	quote;

	nb_quote = 0;
	i = 0;
	while (token->token_s[i])
	{
		quote = is_quote(token->token_s[i]);
		while (quote && token->token_s[i])
		{
			i++;
			if (is_quote(token->token_s[i]) == quote)
			{
				nb_quote += 2;
				break ;
			}
		}
		i++;
	}
	return (i - nb_quote);
}

void	trunc_quote(t_token *token, int i, int j)
{
	int		quote;
	char	*trunc;

	trunc = malloc(trunc_length(token) + 1);
	if (!trunc)
		return ;
	while (token->token_s[i])
	{
		quote = is_quote(token->token_s[i]);
		while (quote && token->token_s[i])
		{
			i++;
			if (is_quote(token->token_s[i]) == quote)
			{
				i++;
				break ;
			}
			trunc[j++] = token->token_s[i];
		}
		if (!quote)
			trunc[j++] = token->token_s[i++];
	}
	trunc[j] = '\0';
	free(token->token_s);
	token->token_s = trunc;
}
