# NAME = minishell

# SRC = $(wildcard *.c)

# CFLAGS = -Wall -Wextra -Werror

# CC = gcc

# OBJ = $(SRC:.c=.o)

# all : $(NAME)

# $(NAME) : $(OBJ)
# 	$(CC) $(OBJ) libreadline.a -lreadline -lncurses -o $(NAME) $(CFLAGS)

# clean :
# 	rm -rf $(OBJ)

# fclean : clean
# 	rm -rf $(NAME)

# re : fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadufer <hadufer@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 13:33:44 by hadufer           #+#    #+#              #
#    Updated: 2021/11/16 10:37:30 by hadufer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -I./Libftprintf/Libft -I./Libftprintf -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) ./Libftprintf/libftprintf.a
	$(CC) $(CFLAGS) -lreadline -lncurses $(OBJS) ./libftprintf/libftprintf.a -o $(NAME)

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
