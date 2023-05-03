# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 11:40:33 by mcourtin          #+#    #+#              #
#    Updated: 2023/05/03 14:50:23 by mcourtin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -lreadline -fsanitize=address -g

SRCS =	srcs/main.c parsing/parser.c parsing/calloc.c parsing/check_operator.c \
		parsing/parser_utils.c parsing/add_token.c parsing/alias_replacer.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	
fclean : clean
		rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re