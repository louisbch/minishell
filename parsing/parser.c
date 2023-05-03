/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:21:06 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/02 16:12:58 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	token_length(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = is_quote(line[i]);
	while (quote && line[i])
	{
		i++;
		if (is_quote(line[i]) == quote)
			return (i + 1);
		if (!line[i])
		{
			printf("error, %c is not closed\n", line[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (check_in(line))
		return (check_in(line));
	if (check_out(line))
		return (check_out(line));
	if (check_pipe(line))
		return (check_pipe(line));
	while (line[i] && !is_operator(line[i]) && !is_quote(line[i]) && line[i] \
	!= ' ')
		i++;
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
	*nb_char = token_length(line);
	new->tokens = malloc(*nb_char + 1);
	while (i < *nb_char)
	{
		new->tokens[i] = line[i];
		i++;
	}
	new->tokens[i] = '\0';
	new->type = 0;
	new->next = NULL;
	return (new);
}

t_token	*tokenizer(char	*line, t_token **token)
{
	int		i;
	int		*nb_char;
	t_token	*new;

	i = 0;
	nb_char = malloc(sizeof(int));
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		new = new_token(&line[i], nb_char);
		if (!new)
			printf("error\n");
		ft_add_back(token, new);
		i += *nb_char;
	}
}

void	parse(char	*line)
{
	t_token	**token;

	token = malloc(sizeof(t_token **) * 1);
	*token = NULL;
	tokenizer(line, token);
	printf("test\n\n");
	while (*token)
	{
		printf("%s\n", (*token)->tokens);
		*token = (*token)->next;
	}
	//alias_replacer(data);
}
