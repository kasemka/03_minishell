

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "libft/libft.h"

int		g_exitcode;

typedef struct s_env {
	char		 	*key_vl;
	char			flag;
	int				printed;
	struct s_env 	*next;
} t_env;


int		msg_error(void);
int		msg_mallocfail(void);
int		len_arr(char **env);
// void	printfList(t_env *lst);
t_env	*arr_to_list(char **env, int env_len);
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
t_env	*last_list(t_env *env);
int		len_lst(t_env *lst);
// char	*find_by_key(t_env *env, char *key);
t_env	*find_by_key(t_env *env, char *key_env);
void	ft_free_2array(char **arr);
char	**list_to_arr(t_env *env);


void	printArr(char **arr);
