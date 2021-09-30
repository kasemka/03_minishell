#include "minishell.h"

// exit??? malloc fail
int	msg_error()
{
	printf("%s\n", strerror(errno));
	exit (1);

}

t_env *arr_to_list(char **env, int env_len)
{
	int		i;
	t_env	*temp;
	t_env	*env_list;

	i = 0;
	temp = NULL;
	while(i < env_len)
	{
		env_list = malloc(sizeof(t_env));
		if (!env_list)
			msg_error();
		env_list->key_value = ft_strdup(env[env_len - i - 1]);
		if (env_list->key_value == NULL)
			msg_error();
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
		printf("%p ", lst);
		printf("%s \n", lst->key_value);
		lst = lst->next;
	}
}

void printArr(char **arr) {
	while (*arr) {
		printf("%s \n", *arr);
		arr++;
	}
}

//flag 1 = env, 2 = export, 3 = set 
void	print_env(t_env *lst, char *args)
{
	int		cmd_flag;


	cmd_flag = 0;
	if (ft_strncmp(args, "env", 4) == 0)
		cmd_flag = 1;
	else if (ft_strncmp(args, "export", 7) == 0)
		cmd_flag = 2;
	else if (ft_strncmp(args, "set_local", 10) == 0)
		cmd_flag = 3;
	while (lst)
	{
		if (cmd_flag == 1 && lst->flag == 1)
			printf("%s \n", lst->key_value);
		else if (cmd_flag == 2 && (lst->flag == 1 || lst->flag == 2))
			printf("%s \n", lst->key_value);
		else if (cmd_flag == 3 && (lst->flag == 1 || lst->flag == 3))
			printf("%s \n", lst->key_value);
		lst = lst->next;
	}
}

int check_export_name(char *key_value)
{
	int i;
	
	i = 0;
	
	if (ft_isalpha(key_value[0]) == 0)
		return (1);
	while (key_value[++i] != '=' && key_value[i] != '\0')
	{
		if (!ft_isalpha(key_value[i]) && !ft_isdigit(key_value[i]) && key_value[i] != '_')
		{
			printf("export: `%s': not a valid identifier\n", key_value);
			return (1);
		}
	}
	return (0);
}

int	len_before_equal(char *str)
{
	char		*char_str;

	char_str = ft_strchr(str, '=');
	if (char_str != NULL)
		return (char_str - str + 1);
	return (0);
}