NAME = minishell

SRC = main.c\
libft/ft_strlen.c\
libft/ft_strnstr.c\
libft/ft_split.c\
libft/ft_strchr.c\
libft/ft_strncmp.c\
libft/ft_strdup.c\
libft/ft_isdigit.c\
libft/ft_isalpha.c\
libft/ft_memcmp.c\
libft/ft_strlcpy.c\
bldin_env.c\
bldin_unset.c\
bldin_pwd.c\
bldin_export.c\
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
