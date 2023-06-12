/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:24:48 by mcourtin          #+#    #+#             */
/*   Updated: 2023/06/12 10:08:47 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD 0
# define PIPE 1
# define O_FILE 2
# define I_FILE 3
# define HERE 4
# define APP 5

int	g_signal;

typedef struct s_token
{
	char				*token_s;
	int					type;
	int					error;
	struct s_token		*next;
	struct s_token		*previous;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/*PARSING*/

t_token	**parse(char	*line, t_env **env);
void	double_link(t_token **token);
void	free_token(t_token **token);
void	get_token_type(t_token **token);
int		check_input(t_token **token);

//		utils

t_env	*new_env(char *envp);
void	add_env_back(t_env **my_env, t_env *new);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
size_t	ft_strlen(const char *s);
int		ft_wordlen(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		is_operator(char c);
int		is_quote(char c);
int		ft_isalnum(int c);
void	ft_add_back(t_token **token, t_token *new);
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
int		replace_by_signal(t_token *token);

//		check operator

int		check_op_len(char *line, t_token *token);
int		check_out(char *line, t_token *token);
int		check_in(char *line, t_token *token);
int		check_pipe(char *line, t_token *token);

//alias handler

void	alias_replacer(t_token **token, t_env **env);
void	trunc_quote(t_token *token, int i, int j);

//env
char	**ft_split(const char *s, char c);
t_env	**init_env(char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

/*BUILTIN*/

void	echo(char **s);
void	env(t_env **env);
void	export(char *str, t_env **my_env);
void	unset(char *name, t_env **my_env);
void	pwd(void);
void	cd(char *path);

//test
void	test_function_print_token(t_token **token);

#endif