/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:13:28 by gvolibea          #+#    #+#             */
/*   Updated: 2021/10/30 12:24:39 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SHL_NAME	"minishell: $"
# define STD_IN		0
# define STD_OUT	1

int		g_exitcode;

typedef struct s_env {
	char			*key_vl;
	char			flg;
	int				printed;
	struct s_env	*next;
}	t_env;

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
	t_env				*env;
} t_pipes;


# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>


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
void get_question(void);
char *get_var(char *str, int *i);
t_parsing	*new_list(void);
void ft_isspace(char *str, int *s_w_i);
int pipe_o_redirect(char *str);
void parser_get_word(char **out, char *str, int start, int *i);
char **add_array_element(t_parsing *parso, char *str, int words_num);
int if_pipe_or_redirect(char c);
t_pipes *new_pipes(t_env *env);
void free_pipes(t_pipes *pipes);
void make_pipes(t_pipes *pipes);
void non_exit_failure(char *err_msg);

// make_redirects
int	make_redirects(t_pipes *pipes);


//arrays operations
char **add_array_array(char **arr1, char **arr2);
void clean_array(char **args);
int size_arr(char **arr);

void	run_commands(char **commands, t_pipes *pipes); //run_commands(char **commands, t_env *env);
int		msg_error(void);
int		msg_error_str(char *s);
int		msg_mallocfail(void);
int		msg_home_not_set(void);
int		msg_error_export(char *s);
int		len_arr(char **env);
int		bldin_cd(t_env *env_list, char **args);
int		bldin_echo(char **args);
int		bldin_env(t_env *env);
int		bldin_exit(char **args);
int		bldin_export(t_env **env_list, char **args);
int		bldin_pwd(t_env *env);
int		bldin_unset(t_env **env_list, char **args);
int		other_cmd(t_env *env, char **commands);
int		len_arr(char **arr);
int		index_strchr(char *str, char c);
void	print_env(t_env *lst, char *args);
int		check_name(char *key_value);
int		len_key(char *str);
int		add_addit_keys(t_env *env);
int		add_pwd(t_env *env);
int		change_env(t_env *env, char **arg);
int		add_new_list(t_env *envp, int flag, int printed);
int		len_lst(t_env *lst, int flag); // edit
void	ft_free_2array(char **arr);
char	**list_to_arr(t_env *env);
t_env	*arr_to_list(char **env, int env_len);
t_env	*find_by_key(t_env *env, char *key_env);
t_env	*last_list(t_env *env);
void	free_list_env(t_env *env);
void	printArr(char **arr);

//signals
void 	sig_ignore(int signo);
void	cancel_cmd(int signo);
void 	quit_cmd(int signo);


#endif
