# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 15:32:53 by hadufer           #+#    #+#              #
#    Updated: 2021/11/25 11:58:03 by nferre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRCS = $(wildcard ./srcs/*.c) $(wildcard ./srcs/lexer/*.c) $(wildcard ./srcs/builtins/*.c) $(wildcard ./srcs/utils/*.c)

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I./Libftprintf/Libft -I./Libftprintf -I./includes -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) ./Libftprintf/libftprintf.a
	$(CC) $(CFLAGS) -lreadline -lncurses $(OBJS) libreadline.a ./libftprintf/libftprintf.a -o $(NAME)

./Libftprintf/libftprintf.a:
	$(MAKE) -C ./Libftprintf

clean:
	$(MAKE) -C ./Libftprintf $@
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./Libftprintf $@
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean flcean re
