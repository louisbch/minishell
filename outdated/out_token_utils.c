/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:21:57 by mcourtin          #+#    #+#             */
/*   Updated: 2023/04/25 14:22:31 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_tokken(char c)
{
	int		i;
	char	*s;

	s = "<>|";
	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

//pour faire des tests
int	char_counter(char *str, char sep)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] != sep)
			c++;
		i++;
	}
	return (c);
}

int	tokens_counter(char *str, char sep)
{
	int	i;
	int	wc;

	if (!str[0])
		return (0);
	i = 1;
	wc = 0;
	if (is_tokken(str[0]) && str[1] != sep && str[1])
		wc++;
	if (str[0] != sep)
		wc++;
	while (str[i])
	{
		if (str[i] != sep && str[i - 1] == sep)
			wc++;
		if (str[i] != sep && is_tokken(str[i + 1]))
			wc++;
		if (is_tokken(str[i]) && (str[i + 1] != sep && str[i + 1] \
		&& !is_tokken(str[i + 1])))
			wc++;
		i++;
	}
	return (wc);
}
