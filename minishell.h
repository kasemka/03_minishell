/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:28:18 by lelle             #+#    #+#             */
/*   Updated: 2021/10/12 14:28:25 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include "libft/libft.h"

int		g_exitcode;

typedef struct s_env {
	char			*key_vl;
	char			flg;
	int				printed;
	struct s_env	*next;
}	t_env;

int		msg_error(void);
int		msg_error_str(char *s);
int		msg_mallocfail(void);
int		len_arr(char **env);
int		bldin_cd(t_env *env_list, char **args);
int		bldin_echo(char **args);
int		bldin_env(t_env *env);
int		bldin_exit(char **args);
int		bldin_export(t_env **env_list, char **args);
int		bldin_pwd(void);
int		bldin_unset(t_env **env_list, char **args);
int		other_cmd(t_env *env, char **commands);
int		len_arr(char **arr);
int		index_strchr(char *str, char c);
void	print_env(t_env *lst, char *args);
int		check_export_name(char *key_value);
int		len_key(char *str);
int		add_addit_home(t_env *env);
int		add_new_list(t_env *envp, int flag, int printed);
int		len_lst(t_env *lst);
void	ft_free_2array(char **arr);
char	**list_to_arr(t_env *env);
t_env	*arr_to_list(char **env, int env_len);
t_env	*find_by_key(t_env *env, char *key_env);
t_env	*last_list(t_env *env);
void	printArr(char **arr);

#endif