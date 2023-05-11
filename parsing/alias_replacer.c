/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replacer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:58:12 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/11 13:43:24 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expander(t_token *token, t_env **my_env)
{
	int		i;
	char	*replaced;

	i = 0;
	while (token->token_s[i])
	{
		if (token->token_s[i] == '$')
		i++;
	}
}

void	alias_replacer(t_token **token, t_env **my_env)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		//expander(tmp, my_env);
		trunc_quote(tmp, 0, 0);
		tmp = tmp->next;
	}
}
