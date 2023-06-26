/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:38:59 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 10:48:26 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_pwd(t_global *global)
{
	char	*pwd;

	global->pwd = getcwd(NULL, 0);
}

void	pwd(t_global *global)
{
	char	*pwd;

	printf("%s\n", global->pwd);
}
