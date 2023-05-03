/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:29:43 by mcourtin          #+#    #+#             */
/*   Updated: 2023/04/25 15:24:33 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*str_token(char *s, int nb_token, int nb_char)
{
	char	*tok;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tok = malloc(sizeof(char) * (nb_char + nb_token));
	while (s[i])
	{
		if (is_tokken(s[i]))
		{
			if (s[i - 1] != ' ' && s[i + 1] != ' ' && i)
			{
				tok[j++] = '\0';
				tok[j++] = s[i++];
				tok[j++] = '\0';
			}
			else if (s[i - 1] != ' ' && i)
			{
				tok[j++] = '\0';
				tok[j++] = s[i++];
			}
			else if (s[i + 1] != ' ')
			{
				tok[j++] = s[i++];
				tok[j++] = '\0';
			}
			else
				tok[j++] = s[i++];
		}
		else if (s[i] == ' ')
		{
			if (i)
				tok [j++] = '\0';
			while (s[i] == ' ')
				i++;
		}
		else
			tok[j++] = s[i++];
	}
	tok[j] = '\0';
	i = 0;
	while (i < nb_char + nb_token)
	{
		if (tok[i] == '\0')
			printf("_");
		else
			printf("%c", tok[i]);
		i++;
	}
	return (tok);
}

int	check_double_red(char **token_tab, char *token_line, int *nb_token, int i)
{
	int	j;

	j = 0;
	if (token_line[j] == '<')
	{
		j += 2;
		if (token_line[j] == '<')
		{
			printf("pare error near '<'\n");
			exit(EXIT_FAILURE);
		}
		j++;
		if (token_line[j] == '<')
		{
			(*nb_token)--;
			token_tab[i] = "<<";
			return (1);
		}
	}
	if (token_line[j] == '>')
	{
		j += 2;
		if (token_line[j] == '>')
		{
			printf("pare error near '>'\n");
			exit(EXIT_FAILURE);
		}
		j++;
		if (token_line[j] == '>')
		{
			(*nb_token)--;
			token_tab[i] = ">>";
			return (1);
		}
	}
	return (0);
}

char	**token_maker(char *line)
{
	int		i;
	int		j;
	char	*token_line;
	char	**token_tab;
	int		nb_char;
	int		nb_token;

	i = 0;
	j = 0;
	nb_token = tokens_counter(line, ' ');
	nb_char = char_counter(line, ' ');
	token_line = str_token(line, nb_token, nb_char);
	while (i < nb_token)
	{
		if (check_double_red(token_tab, &token_line[j], &nb_token, i))
			j += 5;
		else
		{
			token_tab[i] = &token_line[j];
			while (token_line[j])
				j++;
			while (!token_line[j] && i < nb_token - 1)
				j++;
		}
		i++;
	}
	token_tab[i] = NULL;
	//test
	i = 0;
	printf("\nmots : %d\n", nb_token);
	printf("char : %d\n", nb_char);
	while (token_tab[i])
	{
		printf("%s\n", token_tab[i]);
		i++;
	}
	return (token_tab);
}

int	main (int ac, char **av)
{
	token_maker(av[1]);
	return 0;
}