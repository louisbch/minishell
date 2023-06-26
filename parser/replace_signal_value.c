/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_signal_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:24:47 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 12:49:11 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	**return_null_and_val1(void)
{
	g_signal.val = 0;
	return (NULL);
}

int	replace_by_signal(t_token *token)
{
	char	*dollar;
	char	*signal_s;
	char	*after_dollar;
	char	*res;
	int		len;

	dollar = ft_strchr(token->token_s, '$');
	after_dollar = dollar + 2;
	signal_s = ft_itoa(g_signal.val);
	res = ft_calloc(ft_strlen(signal_s) + ft_strlen(token->token_s) - 1, 1);
	if (!res)
		return (0);
	ft_strncpy(res, token->token_s, dollar - token->token_s);
	ft_strcat(res, signal_s);
	ft_strcat(res, after_dollar);
	free(token->token_s);
	token->token_s = res;
	len = ft_strlen(signal_s);
	free(signal_s);
	return (len);
}
