/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:01:34 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 12:07:07 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_cmd(t_token *token)
{
	char	*cmd_path;

	if (access(token->token_s, X_OK | F_OK) == 0)
	{
		cmd_path = ft_strdup(token->token_s);
		if (!cmd_path)
			return (NULL);
		return (cmd_path);
	}
	return (NULL);
}

char	*join_path(t_token *token, char **path, t_env **my_env)
{
	char	*cmd_path;
	int		i;

	i = -1;
	cmd_path = check_cmd(token);
	if (cmd_path)
		return (cmd_path);
	if (!path)
	{
		ft_putstr_fd(token->token_s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], token->token_s);
		if (access(cmd_path, X_OK | F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	**get_path(t_env *my_env)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (my_env)
	{
		if (ft_strnstr(my_env->name, "PATH", 5))
			break ;
		my_env = my_env->next;
	}
	if (!my_env)
		return (NULL);
	path = ft_split(my_env->value, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (path);
}

int	check_builtins(t_cmd *cmd, t_mred *mred, t_global *global)
{
	if (global->cmd == 1 && cmd->builts && cmd->open == 0)
	{
		g_signal.val = exec_builtins(cmd, global);
		if (mred->fd_in == -2)
			heredoc(mred->delim, 0);
		return (1);
	}
	return (0);
}

int	do_execution(t_global *global, t_env **my_env, t_token **token)
{
	t_token	*tmp;
	t_cmd	*cmd;
	t_mred	*mred;
	int		built;

	tmp = *token;
	built = 0;
	if (init_global(global, my_env, tmp))
		return (1);
	cmd = malloc(sizeof(t_cmd) * global->cmd);
	if (!cmd)
		return (1);
	mred = malloc(sizeof(t_mred) * global->cmd);
	if (!mred)
		return (1);
	init_cmd(token, cmd, global, mred);
	built = check_builtins(cmd, mred, global);
	if (built != 1)
		execute(cmd, global, mred);
	ft_free_all(global, mred, cmd);
	if (g_signal.exit != -2 && g_signal.exit != -1)
		d_exit(my_env, g_signal.exit, global);
	if (g_signal.exit == -1)
		d_exit(my_env, EXIT_SUCCESS, global);
	return (0);
}
