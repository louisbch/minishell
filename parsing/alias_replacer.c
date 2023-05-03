/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replacer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:58:12 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/03 15:30:29 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	trunc_simple_quote(t_token *token)
{
	int		i;
	int		len;
	char	*trunc;

	i = 0;
	if (token->tokens[i] != 39)
		return ;
	len = ft_strlen(token->tokens);
	trunc = malloc(len - 1);
	if (!trunc)
	{
		//protection;	
	}
	while (i < len - 2)
	{
		trunc[i] = token->tokens[i + 1];
		i++;
	}
	trunc[i] = '\0';
	free(token->tokens);
	token->tokens = trunc;
}

void	trunc_double_quote(t_token *token)
{
	int		i;
	int		len;
	char	*trunc;

	i = 0;
	if (token->tokens[i] != 34)
		return ;
	len = ft_strlen(token->tokens);
	trunc = malloc(len - 1);
	if (!trunc)
	{
		//protection;	
	}
	while (i < len - 2)
	{
		trunc[i] = token->tokens[i + 1];
		i++;
	}
	trunc[i] = '\0';
	free(token->tokens);
	token->tokens = trunc;
}

void	replace_dollars(t_token *token)
{
	int	i;

	if (token->tokens[0] == 39)
		return ;
	i = 0;
}

void	alias_replacer(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		//replace_dollars(tmp);
		trunc_simple_quote(tmp);
		trunc_double_quote(tmp);
		tmp = tmp->next;
	}
}
