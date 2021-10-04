SRC_S    =   parcer.c help_funcs.c Parser/parser_help.c Parser/parser_help2.c \
			Parser/parser_help3.c  Parser/parser_help_array.c

OBJ_S    =   ${SRC_S:.c=.o}

FLAGS   =   -Wall -Wextra -Werror -I.

NAME	  =	  minishell


${NAME} :  ${OBJ_S}
			cd ./Libft/ && make
			#gcc $(FLAGS) -L./Libft/ -lft -L/usr/include -lreadline -o $(NAME) $(OBJ_S)
			gcc $(FLAGS) -L./Libft/ -lft -L/usr/include -lreadline -o $(NAME) $(OBJ_S)

all:	${NAME}

clean:
			rm -f ${OBJ_S}
			cd ./Libft/ && make clean

fclean:		clean
			rm -f $(NAME)
			cd ./Libft/ && make fclean

re:			fclean all

bonus: 		$(NAME)

.PHONY:		all clean fclean re bonus
