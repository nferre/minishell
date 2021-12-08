# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 17:55:02 by hadufer           #+#    #+#              #
#    Updated: 2021/12/07 10:42:05 by nferre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -g -fsanitize=address

SRCS = $(wildcard ./srcs/*.c) $(wildcard ./srcs/lexer/*.c) $(wildcard ./srcs/builtins/*.c) $(wildcard ./srcs/utils/*.c) $(wildcard ./srcs/builtins/export/*.c)


OBJS = $(SRCS:.c=.o)

%.o: %.c
	echo $(DEBUG_COMPILE)
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
