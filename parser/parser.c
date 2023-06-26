/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:50:56 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/23 12:53:01 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_length(char *line, t_token *token)
{
	int	i;
	int	quote;
	int	ope_len;

	i = 0;
	ope_len = check_op_len(line, token);
	if (ope_len)
		return (ope_len);
	while (line[i] && !is_operator(line[i]) && line[i] != ' ')
	{
		quote = is_quote(line[i]);
		while (quote && line[i])
		{
			i++;
			if (is_quote(line[i]) == quote)
				break ;
			if (!line[i])
			{
				token->error = 1;
				printf("error, %c is not closed\n", quote);
			}
		}
		i++;
	}
	return (i);
}

t_token	*new_token(char *line, int *nb_char)
{
	t_token	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->error = 0;
	*nb_char = token_length(line, new);
	if (new->error == 1)
	{
		free(new);
		return (NULL);
	}
	new->token_s = ft_calloc(1, *nb_char + 1);
	if (!new->token_s)
		return (NULL);
	while (i < *nb_char)
	{
		new->token_s[i] = line[i];
		i++;
	}
	new->type = 0;
	new->next = NULL;
	return (new);
}

static void	free_token_parse(t_token **token)
{
	t_token	*temp;

	while (*token)
	{
		temp = (*token)->next;
		if ((*token)->token_s)
			free ((*token)->token_s);
		free(*token);
		*token = temp;
	}
	*token = NULL;
	if (token)
		free (token);
}

int	tokenizer(char	*line, t_token **token)
{
	int		i;
	int		*nb_char;
	t_token	*new;

	i = 0;
	nb_char = malloc(sizeof(int));
	if (!nb_char)
		return (1);
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		new = new_token(&line[i], nb_char);
		if (!new)
		{
			free_token_parse(token);
			return (free_nb_char(nb_char, 1));
		}
		ft_add_back(token, new);
		i += *nb_char;
	}
	return (free_nb_char(nb_char, 0));
}

t_token	**parse(char *line, t_env **my_env)
{
	t_token	**token;

	if (check_empty_line(line))
		return (return_null_and_val1());
	token = malloc(sizeof(t_token **) * 1);
	if (!token)
		return (NULL);
	*token = NULL;
	if (tokenizer(line, token))
	{
		g_signal.val = 1;
		return (NULL);
	}
	double_link(token);
	get_token_type(token);
	alias_replacer(token, my_env);
	if (check_input(token))
	{
		g_signal.val = 1;
		free_token_parse(token);
		return (NULL);
	}
	return (token);
}
