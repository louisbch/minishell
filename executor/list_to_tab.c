/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:17:52 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/23 17:00:58 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_len(t_env **my_env)
{
	int		i;
	t_env	*tmp;

	if (!my_env)
		return (0);
	i = 0;
	tmp = *my_env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*join_env(t_env *env)
{
	char	*str;
	char	*tmp;

	str = ft_strjoin(env->name, "");
	if (!str)
		return (NULL);
	tmp = ft_strjoin(str, "=");
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	free(str);
	str = ft_strjoin(tmp, env->value);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (str);
}

char	**list_tab(t_env **my_env)
{
	int		i;
	int		nb_env;
	char	**tab;
	t_env	*tmp;

	i = 0;
	tmp = *my_env;
	nb_env = env_len(my_env);
	if (!nb_env)
		return (NULL);
	tab = malloc(sizeof(char *) * nb_env + 1);
	if (!tab)
		return (NULL);
	tab[nb_env] = NULL;
	while (tmp)
	{
		tab[i] = join_env(tmp);
		if (!tab[i++])
		{
			free_tabs(tab);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (tab);
}
