NAME = minishell

SRC = main.c \
	  ft_split.c \
	  echo.c \
	  cd.c \
	  pwd.c \
	  find_exec.c \
	  utils.c

FLAGS = -Wall -Wextra -Werror -lreadline

CC = gcc

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
