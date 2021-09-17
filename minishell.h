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
	struct s_env 	*next;
} t_env;


int		msg_error();
int		len_arr(char **env);
void	printfList(t_env *lst);
void	rm_from_list(t_env *env_list, int i);
t_env	*arr_to_list(char **env, int env_len);
int		ft_unset(t_env *env_list, char *key);
int		bldin_env(char  **args, t_env *env);
int		len_arr(char **arr);
int		index_strchr(char *str, char c);
