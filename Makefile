# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 17:55:02 by hadufer           #+#    #+#              #
#    Updated: 2022/01/15 18:00:53 by hadufer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/builtins/cd.c \
srcs/builtins/check_exec_builtins.c \
srcs/builtins/echo.c \
srcs/builtins/env.c \
srcs/builtins/exit.c \
srcs/builtins/export/export.c \
srcs/builtins/export/realloc_env.c \
srcs/builtins/export/verify.c \
srcs/builtins/pwd.c \
srcs/builtins/unset.c \
srcs/find_exec.c \
srcs/lexer_parser/expand.c \
srcs/lexer_parser/lexer.c \
srcs/lexer_parser/lexer2.c \
srcs/lexer_parser/lexer3.c \
srcs/lexer_parser/lexer4.c \
srcs/lexer_parser/token.c \
srcs/new_main.c \
srcs/new_main_func.c \
srcs/new_main_util.c \
srcs/pipe_exec.c \
srcs/redirect_input_exec.c \
srcs/redirect_input_here_exec.c \
srcs/redirect_out_append_exec.c \
srcs/redirect_out_exec.c \
srcs/utils/dup_double_char_array.c \
srcs/utils/exec_utils.c \
srcs/utils/ft_functions_null.c \
srcs/utils/ft_getenv.c \
srcs/utils/ft_insert_string.c \
srcs/utils/ft_isspace.c \
srcs/utils/ft_remchar.c \
srcs/utils/ft_remstring.c \
srcs/utils/ft_strchr_c.c \
srcs/utils/ft_strjoin_free.c \
srcs/utils/ft_strndup.c \
srcs/utils/get_local_var.c \
srcs/utils/get_tab_length.c \
srcs/utils/init_global_data.c \
srcs/utils/is_empty.c \
srcs/utils/operand.c \
srcs/utils/utils_find_exec.c \
srcs/utils/utils_redirect.c \
srcs/utils/verify_redirect.c \

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
