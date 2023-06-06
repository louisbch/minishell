/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replacer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:58:12 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/06 10:46:39 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_value(t_env **my_env, char *name)
{
	t_env	*tmp;

	tmp = *my_env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	replace_word(t_token *token, char *value, char *word_end, char *dollar)
{
	char	*replace;
	int		total_length;
	int		word_length;

	word_length = ft_wordlen(dollar + 1);
	total_length = ft_strlen(token->token_s) + ft_strlen(value) - word_length;
	replace = ft_calloc(total_length + 1, 1);
	if (!replace)
		return ;
	ft_strncpy(replace, token->token_s, dollar - token->token_s);
	ft_strcat(replace, value);
	ft_strcat(replace, word_end);
	free(token->token_s);
	token->token_s = replace;
}

int	replace_dollar(t_token *token, t_env **my_env)
{
	char	*dollar;
	char	*word;
	char	*value;
	char	*word_end;
	int		word_length;

	dollar = ft_strchr(token->token_s, '$');
	word_length = ft_wordlen(dollar + 1);
	word_end = dollar + word_length + 1;
	word = ft_calloc(word_length + 1, 1);
	if (!word)
		return (0);
	ft_strncpy(word, dollar + 1, word_length);
	value = get_value(my_env, word);
	if (!value)
	{
		value = ft_calloc(1, 1);
		if (!value)
			return (0);
	}
	replace_word(token, value, word_end, dollar);
	free (word);
	return (ft_strlen(value));
}

void	expander(t_token *token, t_env **my_env)
{
	int		i;
	int		quote;
	char	*dollar;

	i = 0;
	while (token->token_s[i])
	{
		if (token->token_s[i] == 39)
		{
			i++;
			while (token->token_s[i] != 39)
				i++;
		}
		if (token->token_s[i] == '$')
		{
			if (ft_strncmp(token->token_s + i, "$?", 2))
				i += replace_by_signal(token);
			else
				i += replace_dollar(token, my_env) - 1;
		}
		i++;
	}
}

void	alias_replacer(t_token **token, t_env **my_env)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		expander(tmp, my_env);
		trunc_quote(tmp, 0, 0);
		tmp = tmp->next;
	}
}
