NAME 	=	minishell

HEADER	=	ft_minishell.h

SRC		=	$(wildcard Bldins/*.c) $(wildcard Parser/*.c) \
				$(wildcard Redirect/*.c) $(wildcard *.c)

LIBFT	=	Libft/libft.a

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror

#%.o:		%.c $(HEADER)
			# $(CC) -g $(FLAGS) -c -o $@ $<

$(NAME):	$(OBJ) $(HEADER)
			$(MAKE) -C ./Libft
			#$(CC) -g $(FLAGS) $(OBJ) -L./Libft/ -lft  \
			-o $(NAME) -L/usr/include -lreadline
			$(CC) -g $(FLAGS) $(OBJ) -L./Libft/ -o $(NAME) \
			-lreadline -L /User/dp/.brew/opt/readline/lib -I /User/dp/.brew/opt/readline/include
			#~/.brew/opt/readline/include -lreadline -L ~/.brew/opt/readline/lib
			#rm -f $(OBJ)

all:		$(NAME)cd

clean:
			$(MAKE) clean -C ./Libft
			rm -f $(OBJ)

fclean:		clean
			$(MAKE) fclean -C ./Libft
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
