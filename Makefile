NAME 	=	minishell

HEADER	=	ft_minishell.h

SRC		=	$(wildcard Bldins/*.c) $(wildcard Parser/*.c) \
				$(wildcard Redirect/*.c) $(wildcard *.c)

LIBFT	=	Libft/libft.a

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror


%.o:		%.c $(HEADER)
			$(CC) -g $(FLAGS) -c -o $@ $< -I ./Libft -I /Users/$(USER)/.brew/include

$(NAME):	$(OBJ) $(HEADER)
			$(MAKE) -C ./Libft
			$(CC) $(OBJ) $(LIBFT) -I ./Libft -I /Users/$(USER)/.brew/include -o ${NAME} -lreadline -L /Users/$(USER)/.brew/opt/readline/lib 

all:		$(NAME)

clean:
			$(MAKE) clean -C ./Libft
			rm -f $(OBJ)

fclean:		clean
			$(MAKE) fclean -C ./Libft
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re