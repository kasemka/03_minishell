NAME 	=	minishell

HEADER	=	minishell.h

SRC		=	$(wildcard *.c)

LIBFT	=	libft/libft.a

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror

%.o:		%.c $(HEADER)
			$(CC) -g $(FLAGS) -c -o $@ $<

$(NAME):	$(OBJ) $(HEADER)
			$(MAKE) -C ./libft
			$(CC) -g $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)
			rm -f $(OBJ)

all:		$(NAME)

clean:
			$(MAKE) clean -C ./libft
			rm -f $(OBJ)

fclean:		clean
			$(MAKE) clean -C ./libft
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
