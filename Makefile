# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 17:55:02 by hadufer           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/01/08 10:03:35 by nferre           ###   ########.fr        #
=======
#    Updated: 2022/01/07 18:48:49 by hadufer          ###   ########.fr        #
>>>>>>> cdf797d01741ae05104c69bc73ddd96c9087c1aa
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -g

SRCS = $(wildcard ./srcs/*.c) $(wildcard ./srcs/lexer_parser/*.c) $(wildcard ./srcs/builtins/*.c) $(wildcard ./srcs/utils/*.c) $(wildcard ./srcs/builtins/export/*.c)


OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I./Libftprintf/Libft -I./Libftprintf -I./includes -c $< -o $@

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
