# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 17:55:02 by hadufer           #+#    #+#              #
#    Updated: 2022/01/12 18:43:08 by hadufer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -g -fsanitize=address

SRCS = $(wildcard ./srcs/*.c) $(wildcard ./srcs/lexer_parser/*.c) $(wildcard ./srcs/builtins/*.c) $(wildcard ./srcs/utils/*.c) $(wildcard ./srcs/builtins/export/*.c)


OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I./Libftprintf/Get_next_line -I./Libftprintf/Libft -I./Libftprintf -I./includes -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) ./Libftprintf/libftprintf.a
	$(CC) $(CFLAGS) $(OBJS) -lreadline -lncurses libreadline.a ./libftprintf/libftprintf.a -o $(NAME)

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
