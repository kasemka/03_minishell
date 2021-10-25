NAME 	=	minishell

HEADER	=	ft_minishell.h

SRC		=	$(wildcard Bldins/*.c) $(wildcard Parser/*.c) $(wildcard Redirect/*.c)

LIBFT	=	Libft/libft.a

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror

#%.o:		%.c $(HEADER)
			#$(CC) -g $(FLAGS) -c -o $@ $<

$(NAME):	$(OBJ) $(HEADER)
			$(MAKE) -C ./libft
			$(CC) -g $(FLAGS) $(OBJ) -L./Libft/ -lft -L/usr/include \
			-lreadline -o $(NAME)
			#rm -f $(OBJ)

all:		$(NAME)

clean:
			$(MAKE) clean -C ./Libft
			rm -f $(OBJ)

fclean:		clean
			$(MAKE) fclean -C ./Libft
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
