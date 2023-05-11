# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 11:40:33 by mcourtin          #+#    #+#              #
#    Updated: 2023/05/11 12:26:21 by mcourtin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -lreadline -fsanitize=address -g

SRCS =	main.c parsing/parser.c utils/calloc.c parsing/check_operator.c \
		parsing/parser_utils.c parsing/add_token.c parsing/alias_replacer.c \
		parsing/quote_trunc.c utils/ft_split.c env/get_env_struct.c \
		utils/int_string.c		
		
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