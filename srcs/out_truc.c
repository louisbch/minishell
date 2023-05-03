/* ************************************************************************** */
/*	                                                    					  */
/*                                                        :::      ::::::::   */
/*   truc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:34:34 by mcourtin          #+#    #+#             */
/*   Updated: 2023/04/17 13:36:08 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define WORD 0
#define PIPE 1
#define I_RED 2
#define O_RED 3

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	which_type(char *s)
{
	if (!strncmp(s, "|", 2))
		return (PIPE);
	if (!strncmp(s, "<", 2))
		return (I_RED);
	if (!strncmp(s, ">", 2))
		return (O_RED);
	return (WORD);
}

t_struct	*struct_builder(char **tokens, int nb_tokens)
{
	int			i;
	t_struct	*tab;

	i = 0;
	tab = malloc(sizeof(t_struct) * (nb_tokens + 1));
	while (tokens[i])
	{
		tab[i].tokens = tokens[i];
		tab[i].type = which_type(tokens[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
