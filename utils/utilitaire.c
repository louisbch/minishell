/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:27:53 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/16 15:43:37 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_wordlen(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = i;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (is_quote(str[i - 1]) && i > 0)
		return (i - 1);
	return (i);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (dest[i] != '\0')
		i++;
	while (src[u] != '\0')
		dest[i++] = src[u++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
