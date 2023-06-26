/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:43:25 by lbouchon          #+#    #+#             */
/*   Updated: 2023/06/26 11:16:36 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <termios.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char				*token_s;
	int					error;
	int					type;
	struct s_token		*next;
	struct s_token		*previous;
}	t_token;

typedef struct sign
{
	int			val;
	int			exit;
}	t_sign;

t_sign	g_signal;

typedef struct s_cmd
{
	char	*cmd;
	char	*cmd_path;
	char	**args;
	char	*builts;
	int		open;
}	t_cmd;

typedef struct s_mred
{
	char	*infile;
	int		fd_in;
	char	*outfile;
	int		fd_out;
	char	*delim;
	int		error;
}	t_mred;

typedef struct s_global
{
	t_token	*first;
	char	*pwd;
	char	**path;
	int		cmd;
	t_env	**my_env;
	char	**envp;
	int		**fd;
}	t_global;

# define CMD 0
# define PIPE 1
# define O_FILE 2
# define I_FILE 3
# define HERE 4
# define APP 5

/*--EXECUTOR--*/

/*--DO_EXECUTION.C--*/

char	*check_cmd(t_token *token);
int		do_execution(t_global *global, t_env **my_env, t_token **token);
char	**get_path(t_env *my_env);
char	*join_path(t_token *token, char **path, t_env **my_env);

/*--INIT_CMD.C && utils --*/

void	init_cmd(t_token **token, t_cmd *cmd, t_global *global, t_mred *mred);
char	*str_lower(char *s);
void	init_built_cmd(t_token **token, t_cmd *cmd, t_global *global, int i);
int		is_builtins(t_token *token, t_cmd *cmd);
void	init_cmd_help(t_token **token, t_cmd *cmd, t_global *global);
void	init_redir(t_cmd *cmd, t_token **token, int count);

/*--PROCESS.C--*/

int		ft_process(pid_t *pid, t_global *global, t_cmd *cmd, t_mred *mred);
int		**create_fd_and_pipe(t_global *global);
int		ft_create_pipe(int **fd, t_global *global);

/*--PROCESS_UTILS.C--*/

int		ft_close_fd(t_global *global);
void	wait_child(pid_t *id, t_global *global);
int		count_cmd(t_token *token);

/*--HEREDOC.C--*/

void	heredoc(char *str, int a);
int		init_global(t_global *global, t_env **my_env, t_token *token);

/*--EXEC_BUILTINS.C--*/

int		exec_builtins(t_cmd *cmd, t_global *global);

/*--ERROR.C--*/

int		ft_no_file(int fd, char *name);
void	ft_error_cmd(char *cmd);
void	ft_free_strs(char *str, char **strs);

/*--REDIRECTION.C--*/

int		ft_redir(t_mred *redir, t_global *global, t_cmd *cmd);

/*--REDIR_FILE.C--*/

int		redir_file(t_cmd *cmd, int i, int j);

/*--EXECUTE.C--*/

int		execute(t_cmd *cmd, t_global *global, t_mred *mred);
void	read_line(char *line, char *stash, char *str, int *fd);
int		is_heredoc(t_cmd *cmd, t_global *global, t_mred *mred);

/*--PARSER--*/

/*--ADD_TOKEN.C--*/

void	ft_add_back(t_token **token, t_token *new);

/*--PARSER.C--*/

int		token_length(char *line, t_token *token);
t_token	*new_token(char *line, int *nb_char);
int		tokenizer(char	*line, t_token **token);
t_token	**parse(char *line, t_env **my_env);
bool	is_space(char c);

/*--FREE.C--*/

void	free_token(t_global *global);
void	ft_free_struct(t_cmd *cmd, t_global *global);
void	free_env(t_env *env);
int		free_myenv(t_env **my_env);
int		free_nb_char(int *i, int a);
t_env	*free_dirty(t_env *env, char **tab);
void	free_tabs(char **tab);
void	ft_free_all(t_global *global, t_mred *mred, t_cmd *cmd);
void	ft_free_path(t_global *global);

/*--CHECK_INPUT.C--*/

int		check_token_multiple_operator(t_token **token);
int		check_token_pipe(t_token **token);
int		check_input(t_token **token);
bool	check_empty_line(char *line);

/*--ALIAS_REPLACER.C--*/

char	*get_value(t_env **my_env, char *name);
void	replace_word(t_token *token, char *value, char *word_end, char *dollar);
int		replace_dollar(t_token *token, t_env **my_env);
void	expander(t_token *token, t_env **my_env);
void	alias_replacer(t_token **token, t_env **my_env);

/*--PARSER_UTILS.C--*/

int		is_quote(char c);
int		is_operator(char c);
void	double_link(t_token **token);
void	get_token_type(t_token **token);

/*--CHECK_OPERATOR.C--*/

int		check_op_len(char *line, t_token *token);
int		check_in(char *line, t_token *token);
int		check_out(char *line, t_token *token);
int		check_pipe(char *line, t_token *token);

/*--ENV--*/

void	augment_shlvl(t_env *new);
t_env	*new_env(char *envp);
void	add_env_back(t_env **my_env, t_env *new);
int		env_maker(t_env **my_env, char **envp);
t_env	**init_env(char **envp);
void	no_shlvl(t_env **my_env);
char	*ft_strdup(const char *s1);
void	set_pwd(t_global *global);

/*--BUILTINS--*/

int		env(char **args, t_env **my_env);
void	echo(t_cmd *cmd);
int		cd(t_cmd *cmd, t_global *global);
int		ft_exit(t_global *global, t_cmd *cmd);
void	pwd(t_global *global);
int		export(char **args, t_env **my_env);
int		export_one(char *args, t_env **my_env);
void	unset(char **args, t_env **my_env);
int		ft_isdigit(int c);
bool	only_number(char *args);

/*--REPLACE_SIGNAL_VALUE.C--*/

int		replace_by_signal(t_token *token);

/*--QUOTE_TRUNC.C--*/

int		trunc_length(t_token *token);
void	trunc_quote(t_token *token, int i, int j);

/*--UTILS--*/

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_wordlen(const char *str);
int		ft_isalnum(int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*--SIGNALS--*/

void	set_signals(void);
void	handle_sigint(int sig);

void	minit_cmd(t_token **token, t_cmd *cmd, t_global *global);
void	mat_redir(t_token **token, t_mred *mred, t_global *global);
void	modif_in(t_token *tmp, t_mred *mred);
void	modif_out(t_token *tmp, t_mred *mred);
void	modif_app(t_token *tmp, t_mred *mred);
void	modif_here(t_token *tmp, t_mred *mred);
char	**list_tab(t_env **my_env);
void	define_builtin_type(t_cmd *cmd);
void	d_exit(t_env **my_env, int exit, t_global *global);
void	cmp_builtin_env(t_cmd *cmd, t_token *token);
t_token	**return_null_and_val1(void);

#endif