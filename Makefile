NAME = minishell

SRC = main.c \
	  ft_split.c \
	  echo.c \
	  cd.c \
	  pwd.c \
	  find_exec.c \
	  utils.c \

CFLAGS = -Wall -Wextra -Werror

CC = gcc

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) libreadline.a -lreadline -lncurses -o $(NAME) $(CFLAGS)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
