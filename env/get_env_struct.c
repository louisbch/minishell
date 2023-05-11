/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:13:49 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/11 13:02:26 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*augment_shlvl(t_env *new, char **tmp)
{	
	int	shlvl;

	new->name = tmp[0];
	shlvl = ft_atoi(tmp[1]) + 1;
	free (tmp[1]);
	tmp[1] = ft_itoa(shlvl);
	new->value = tmp[1];
	new->next = NULL;
	return (new);
}

t_env	*new_env(char *envp)
{
	t_env	*new;
	char	**tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_split(envp, '=');
	if (!tmp)
		return (NULL);
	if (!ft_strncmp(tmp[0], "SHLVL", 5))
		return (augment_shlvl(new, tmp));
	new->name = tmp[0];
	new->value = tmp[1];
	new->next = NULL;
	return (new);
}

void	add_env_back(t_env **my_env, t_env *new)
{
	t_env	*tmp;

	if (!my_env || !new)
		return ;
	if (!*my_env)
		*my_env = new;
	else
	{
		tmp = *my_env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	env_maker(t_env **my_env, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = new_env(envp[i]);
		add_env_back(my_env, new);
		i++;
	}
}

t_env	**init_env(char **envp)
{
	t_env	**my_env;

	my_env = malloc(sizeof(t_env *));
	if (!my_env)
		return (NULL);
	*my_env = NULL;
	env_maker(my_env, envp);
	env(my_env);
	return (my_env);
}
