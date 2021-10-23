/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:13:28 by gvolibea          #+#    #+#             */
/*   Updated: 2021/10/23 15:53:23 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SHL_NAME	"\033[32mgoonndy$ \033[0m"
# define STD_IN		0
# define STD_OUT	1

typedef struct s_parsing
{
	char				**args;
	int					real_empty_str;
	char				*redirects;
	struct s_parsing	*next;
} t_parsing;

typedef struct parse_pipes
{
	t_parsing			*parso;
	struct parse_pipes	*next;
	int					fd_pipes[2];
	int					fd_in;
	int					fd_out;
} t_pipes;

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

void print_list(t_pipes *pipes); //take out later
void free_list(t_parsing *commons);
char *exit_failure(t_pipes *pipes, char *out);
void parser_get_slash(char **out, char *str, int *i, t_parsing *parso);
void parser_get_dollar(char **out, int *i, char *str);
void parser_get_dollar_alone(char **out);
void parser_get_zero_o_space(char **out, t_pipes **pipes, int *s_w_i, \
	char *str);
char *get_dollar(int *i, char *str, char *out);
char *get_quotes(int *i, char *str, char *out);
char *get_question(void);
char *get_var(char *str, int *i);
t_parsing	*new_list(void);
void ft_isspace(char *str, int *s_w_i);
int pipe_o_redirect(char *str);
void parser_get_word(char **out, char *str, int start, int *i);
char **add_array_element(t_parsing *parso, char *str, int words_num);
int if_pipe_or_redirect(char c);
t_pipes *new_pipes(void);
void free_pipes(t_pipes *pipes);
void make_pipes(t_pipes *pipes);

// make_redirects
int	make_redirects(t_pipes *pipes);


//arrays operations
char **add_array_array(char **arr1, char **arr2);
void clean_array(char **args);
int size_arr(char **arr);

#endif
