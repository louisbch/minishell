/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:51:13 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/16 15:29:42 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	nb_char(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		l;
	char		*nb;
	long int	c;

	c = n;
	l = nb_char(c);
	nb = malloc(sizeof(char) * l + 1);
	if (!nb)
		return (0);
	nb[l--] = '\0';
	if (c == 0)
		nb[0] = 48;
	if (c < 0)
	{
		nb[0] = '-';
		c *= -1;
	}
	while (c > 0)
	{
		nb[l--] = c % 10 + 48;
		c /= 10;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			s;
	long int	f;
	long int	ftmp;

	f = 0;
	s = 1;
	i = 0;
	ftmp = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	while (str[i] <= '9' && str [i] >= '0')
	{
		f = f * 10 + (str[i++] - 48);
		if (ftmp > f && s == 1)
			return (-1);
		if (ftmp > f && s == -1)
			return (0);
		ftmp = f;
	}
	return ((int)f * s);
}

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

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if ((char) c == '\0' && s[i] == '\0')
		return ((char *) &s[i]);
	return (0);
}
