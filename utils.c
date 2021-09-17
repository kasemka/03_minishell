#include "minishell.h"

int	msg_error()
{
	printf("%s\n", strerror(errno));
	exit (1);

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
		env_list->key_value = env[env_len - i - 1];
		env_list->flag = 1;
		env_list->next = temp;
		temp = env_list;
		i++;
	}
	return  (env_list);
}

int len_arr(char **arr)
{
	int len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

void printfList(t_env *lst) {
	while (lst) {
		printf("%s \n", lst->key_value);
		lst = lst->next;
	}
}

//index of first founc char in 
int	index_strchr(char *str, char c)
{
	int index;

	index = (int)(strchr(str, c) - str);
	return (index);
}

//flag 1 = env, 2 = export, 3 = set 

void	print_env_flag(t_env *lst, int flag)
{
	while (lst)
	{
		if (lst->flag == flag)
		{
			printf("%s \n", lst->key_value);
		}
		lst = lst->next;
	}
}