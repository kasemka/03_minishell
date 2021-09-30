#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>



typedef struct s_env {
	char		 	*key_value;
	char			flag;
	int				printed;
	struct s_env 	*next;
} t_env;


int		msg_error();
int		len_arr(char **env);
void	printfList(t_env *lst);
t_env	*arr_to_list(char **env, int env_len);
int		bldin_env(t_env *env);
int		bldin_unset(t_env **env_list, char **args);
int		bldin_export(t_env **env_list, char **args);
int		bldin_pwd(void);
int		bldin_echo(t_env **env_list, char **args);
int		len_arr(char **arr);
int		index_strchr(char *str, char c);
void	print_env(t_env *lst, char *args);
int		check_export_name(char *key_value);
int		len_before_equal(char *str);

void	printArr(char **arr);
