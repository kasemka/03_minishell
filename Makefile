NAME = minishell

SRC = main.c\
libft/ft_strlen.c\
libft/ft_strnstr.c\
libft/ft_split.c\
libft/ft_strchr.c\
libft/ft_strncmp.c\
bldin_env.c\
bldin_unset.c\
utils.c


HEADER = minishell.h
OBJ = $(SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror

%.o: %.c $(HEADER)
		$(CC) -g $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
		$(CC) -g $(FLAGS) -o $@ $^ 
		rm -f $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
