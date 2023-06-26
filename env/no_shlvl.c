/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:23:32 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/23 16:32:44 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tabs(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free (tab);
		tab = NULL;
	}
}

t_env	*free_dirty(t_env *env, char **tab)
{
	free_tabs(tab);
	free_env(env);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!dst)
		return (0);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	free_env(t_env *env)
{
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
	}
}

void	no_shlvl(t_env **my_env)
{
	t_env	*tmp;
	t_env	*lvl;

	tmp = *my_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "SHLVL", 5))
		{
			augment_shlvl(tmp);
			return ;
		}
		tmp = tmp->next;
	}
	lvl = malloc(sizeof(t_env));
	if (!lvl)
		return ;
	lvl->name = ft_strdup("SHLVL");
	if (!lvl->name)
		return (free_env(lvl));
	lvl->value = ft_strdup("1");
	if (!lvl->value)
		return (free_env(lvl));
	add_env_back(my_env, lvl);
}
