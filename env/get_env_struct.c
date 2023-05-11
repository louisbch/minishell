/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:13:49 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/11 12:25:45 by mcourtin         ###   ########.fr       */
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

void	add_env_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !new)
		return ;
	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	env_maker(t_env **env, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = new_env(envp[i]);
		add_env_back(env, new);
		i++;
	}
}

t_env	**init_env(char **envp)
{
	t_env	**env;

	env = malloc(sizeof(t_env *));
	if (!env)
		return (NULL);
	*env = NULL;
	env_maker(env, envp);
	printf("env maker :\n\n");
	while (*env)
	{
		printf("%s", (*env)->name);
		printf("=%s\n", (*env)->value);
		*env = (*env)->next;
	}
	return (env);
}
