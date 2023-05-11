/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:24:48 by mcourtin          #+#    #+#             */
/*   Updated: 2023/05/11 11:15:43 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	*line_readline;
	char	*line_with_space;
}	t_data;

typedef struct s_token
{
	char				*token_s;
	int					type;
	struct s_token		*next;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/*PARSING*/

//

void	parse(char	*line);

//		utils

char	*ft_strncpy(char *dest, char *src, unsigned int n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
int		is_operator(char c);
int		is_quote(char c);
void	ft_add_back(t_token **token, t_token *new);

//		check operator

int		check_out(char *line);
int		check_in(char *line);
int		check_pipe(char *line);

//alias handler

void	alias_replacer(t_token **token);
void	trunc_quote(t_token *token, int i, int j);


#endif