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

void rm_from_list(t_env *env_list, int i)
{
	int		j;
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*free_old;

	tmp = env_list;
	tmp2 = env_list;
	j = 0;
	//	printfList(env_list);
	while (j <= i)
	{
		if (j == i)
		{
			//			printf("\nhere\n\n");
			tmp2 = tmp2->next;
			tmp->next = NULL;
			*env_list = *tmp2;
			break;
		}
		else if (j == i - 1 && tmp->next->next == NULL)
		{
			tmp->next = NULL;
			break ;
		}
		else if (j == i - 1 && tmp->next->next != NULL)
		{
			free_old = tmp->next;
			tmp->next = tmp->next->next;
			free_old->next = NULL;
			free(free_old);
			break ;
		}
		tmp = tmp->next;
		j++;
	}
}