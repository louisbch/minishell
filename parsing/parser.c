/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:21:06 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/12 10:04:22 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_length(char *line, t_token *token)
{
	int	i;
	int	quote;

	i = 0;
	if (check_op_len(line, token))
		return (check_op_len(line, token));
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
				return (1);
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
		new = new_token(&line[i], nb_char);
		if (!new)
		{
			free (nb_char);
			free_token(token);
			return (1);
		}
		ft_add_back(token, new);
		i += *nb_char;
	}
	free(nb_char);
	return (0);
}

//test
void	test_function_print_token(t_token **token)
{
	printf("\nparsing :\n");
	while (*token)
	{
		printf(" %d\t", (*token)->type);
		printf("%s\n", (*token)->token_s);
		*token = (*token)->next;
	}
}

int	parse(char	*line, t_env **my_env)
{
	t_token	**token;

	token = malloc(sizeof(t_token **) * 1);
	if (!token)
		return (1);
	*token = NULL;
	if (tokenizer(line, token))
		return (1);
	double_link(token);
	get_token_type(token);
	alias_replacer(token, my_env);
	if (check_input(token))
	{
		free_token(token);
		return (1);
	}
	//test_function_print_token(token);
	return (0);
}
