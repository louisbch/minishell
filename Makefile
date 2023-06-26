# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 13:42:37 by lbouchon          #+#    #+#              #
#    Updated: 2023/06/23 16:04:07 by mcourtin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
RM = rm -rf
DIR = executor/
DIR1 = parser/
BU = builtins/
ENV = env/
UT = utils/
CFLAGS = -Wall -Wextra -Werror -lreadline
NORMINETTE = norminette

SRCS =	main.c							\
		test.c							\
		$(DIR)init_cmd.c				\
		$(DIR)do_execution.c			\
		$(DIR)error.c					\
		$(DIR)exec_builts.c				\
		$(DIR)process.c					\
		$(DIR)redirection.c				\
		$(DIR)process_utils.c			\
		$(DIR)execute.c					\
		$(DIR)heredoc.c					\
		$(DIR)init_cmd_utils.c			\
		$(DIR)redir_utils.c				\
		$(DIR1)add_token.c				\
		$(DIR1)alias_replacer.c			\
		$(DIR1)check_operator.c			\
		$(DIR1)free2.c					\
		$(DIR1)parser_utils.c			\
		$(DIR1)parser.c					\
		$(DIR1)replace_signal_value.c	\
		$(DIR1)free.c					\
		$(DIR1)quote_trunc.c			\
		$(DIR1)check_input.c			\
		$(ENV)get_env_struct.c			\
		$(ENV)no_shlvl.c				\
		$(BU)env.c						\
		$(BU)echo.c						\
		$(BU)cd.c						\
		$(BU)exit.c						\
		$(BU)export.c					\
		$(BU)pwd.c						\
		$(BU)unset.c					\
		$(UT)calloc.c					\
		$(UT)ft_split.c					\
		$(UT)utils2.c					\
		$(UT)int_string.c				\
		$(UT)utils.c					\
		signals/signal.c				\
		executor/list_to_tab.c			\

OBJS = ${SRCS:.c=.o}

all	: ${NAME}

${NAME} : ${OBJS}
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
		@echo "\033[0;42mMinishell is now compile !\033[0m"

clean :
		$(RM) $(OBJS)

fclean : clean
	${RM} ${NAME}

re : fclean all

%.o: %.c
		@echo "\033[1;33mCompiling Minishell...\033[0m"
		${CC} ${FLAGS} -o $@ -c $<

norm :
		${NORMINETTE}

.PHONY: all clean fclean re norm