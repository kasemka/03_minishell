#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

typedef struct s_env {
	char		 	*key;
	struct s_env 	*next;
} t_env;

int	msg_error()
{
	printf("%s\n", strerror(errno));
	exit (1);

}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while(env[i] != 0)
		i++;
	return (i);
}

void printfList(t_env *lst) {
	while (lst) {
		printf("%s \n", lst->key);
		lst = lst->next;
	}
}

t_env *arr_to_list(char **env, int env_len)
{
	int		i;
	//	int 	j;
	t_env	*temp;
	t_env	*env_list;

	i = 0;
	temp = NULL;
	while(i < env_len)
	{
		env_list = malloc(sizeof(t_env));
		if (!env_list)
			msg_error();
		env_list->key = env[env_len - i - 1];
		env_list->next = temp;
		temp = env_list;
		i++;
	}
	return  (env_list);
}


// команды и ключи в листе
int main(int argc, char **argv, char **env)
{
	int i;
	t_env env_list;

	(void)argv;
	i = 0;
	if (argc == 1)
	{
		printf("not enough argv\n");
		exit (1);
	}
	env_list = *arr_to_list(env, env_len(env));
	printfList(&env_list);
	return (0);
}
