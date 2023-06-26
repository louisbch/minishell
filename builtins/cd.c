/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:34:57 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 10:55:14 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_pwd_env(char *pwd, t_env **my_env, char *old_pwd)
{
	t_env	*tmp;
	char	*str;

	str = ft_strjoin("OLDPWD=", old_pwd);
	if (!str)
		return ;
	tmp = *my_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 5))
		{
			free(tmp->value);
			tmp->value = strdup(pwd);
		}
		tmp = tmp->next;
	}
	export_one(str, my_env);
	free(str);
}

void	update_pwd(t_global *global)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	replace_pwd_env(pwd, global->my_env, global->pwd);
	free(global->pwd);
	global->pwd = pwd;
}

char	*cd_absolute_path(char *arg, t_global *global)
{
	char	*pwd;
	char	*tmp;
	char	*abs;

	if (arg[0] == '/')
		return (arg);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	tmp = ft_strjoin(global->pwd, "/");
	if (!tmp)
		return (NULL);
	abs = ft_strjoin(tmp, arg);
	free (tmp);
	if (!abs)
		return (NULL);
	return (abs);
}

int	cd(t_cmd *cmd, t_global *global)
{	
	int		res;
	char	*path;

	if (!cmd->args[1])
		return (0);
	path = cd_absolute_path(cmd->args[1], global);
	res = chdir(path);
	if (res == -1)
	{
		ft_putstr_fd("cd:", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	update_pwd(global);
	return (0);
}
