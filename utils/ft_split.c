/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:37:09 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/12 16:27:23 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	words_counter(const char *str, char sep)
{
	int	i;
	int	wc;

	if (!str[0])
		return (0);
	i = 1;
	wc = 0;
	if (str[0] != sep)
		wc++;
	while (str[i])
	{
		if (str[i] != sep && str[i - 1] == sep)
			wc++;
		i++;
	}
	return (wc);
}

static int	wordlen(const char *str, char sep, int start)
{
	int	i;

	i = start;
	while (str[i] && str[i] != sep)
		i++;
	return (i - start);
}

char	**ft_free_return(char **tab, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
		free(tab[i++]);
	free(tab);
	return (0);
}

char	**ft_split2(const char *s, char c, int i, int k)
{
	char	**dst;
	int		j;

	dst = malloc(sizeof(char *) * (words_counter(s, c) + 1));
	if (!dst)
		return (NULL);
	while (s[++i])
	{
		j = -1;
		if (s[i] != c)
		{
			dst[k] = malloc(sizeof(char) * (wordlen(s, c, i)) + 1);
			if (!dst[k])
				return (ft_free_return(dst, k));
			while (++j < wordlen(s, c, i))
				dst[k][j] = s[i + j];
			dst[k++][j] = '\0';
			i += j - 1;
		}
	}
	dst[k] = 0;
	return (dst);
}

char	**ft_split(const char *s, char c)
{
	char	**dst;
	int		i;
	int		k;

	i = -1;
	k = 0;
	if (!s)
		return (0);
	dst = ft_split2(s, c, i, k);
	return (dst);
}
