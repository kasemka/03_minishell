/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:13:28 by gvolibea          #+#    #+#             */
/*   Updated: 2021/10/04 22:22:16 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SHL_NAME	"\033[32mgoonndy$ \033[0m"

typedef struct s_parsing
{
	char				**args;
	char				*red_o_pipe;
	struct s_parsing	*next;
} t_parsing;

# include "Libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

void print_list(t_parsing *parso); //take out later
void free_list(t_parsing *commons);
char *exit_failure(t_parsing *parso, char *out);
void parser_get_slash(char **out, char *str, int *i);
void parser_get_dollar(char **out, int *i, char *str);
void parser_get_dollar_alone(char **out);
int parser_list_update(char **out, t_parsing **parso);
void parser_get_zero_o_space(char **out, t_parsing **parso, int *words_num);
char *get_dollar(int *i, char *str, char *out);
char *get_quotes(int *i, char *str, char *out);
char *get_question(void);
char *get_var(char *str, int *i);
t_parsing	*new_list(void);
void ft_isspace(char **str);
int pipe_o_redirect(char *str);
void parser_get_word(char **out, char *str, int start, int *i);
char **add_array_element(t_parsing *parso, char *str, int words_num);

#endif
