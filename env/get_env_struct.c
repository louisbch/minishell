/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:30:09 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 10:41:09 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	augment_shlvl(t_env *new)
{	
	int	shlvl;

	shlvl = ft_atoi(new->value) + 1;
	free (new->value);
	new->value = ft_itoa(shlvl);
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
	{
		free_env(new);
		return (NULL);
	}
	new->name = ft_strdup(tmp[0]);
	if (!new->name)
		return (free_dirty(new, tmp));
	if (tmp[1])
		new->value = ft_strdup(tmp[1]);
	else
		new->value = ft_calloc(1, 1);
	if (!new->value)
		return (free_dirty(new, tmp));
	free_tabs(tmp);
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
		new->next = NULL;
	}
}

int	env_maker(t_env **my_env, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = new_env(envp[i]);
		if (!new)
			return (free_myenv(my_env));
		add_env_back(my_env, new);
		i++;
	}
	if (!*my_env)
		return (1);
	return (0);
}

t_env	**init_env(char **envp)
{
	t_env	**my_env;

	my_env = malloc(sizeof(t_env *));
	if (!my_env)
		return (NULL);
	*my_env = NULL;
	if (env_maker(my_env, envp))
		return (NULL);
	no_shlvl(my_env);
	return (my_env);
}
