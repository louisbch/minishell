/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_signal_vaue.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:33:20 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/06 10:47:10 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	replace_by_signal(t_token *token)
{
	char	*dollar;
	char	*signal_s;
	char	*after_dollar;
	char	*res;

	dollar = ft_strchr(token->token_s, '$');
	after_dollar = dollar + 2;
	signal_s = ft_itoa(g_signal);
	res = ft_calloc(ft_strlen(signal_s) + ft_strlen(token->token_s) - 1, 1);
	if (!res)
		return (0);
	ft_strncpy(res, token->token_s, dollar - token->token_s);
	ft_strcat(res, signal_s);
	ft_strcat(res, after_dollar);
	free(token->token_s);
	token->token_s = res;
	return (ft_strlen(signal_s));
}
