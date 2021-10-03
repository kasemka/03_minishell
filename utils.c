#include "minishell.h"

// exit??? malloc fail
int	msg_error()
{
	printf("%s\n", strerror(errno));
	return (0);

}

//change code after malloc error!!!!!!!!!!!!!!!!!!!!!!!!!!
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
		env_list->key_val = ft_strdup(env[env_len - i - 1]);
		if (env_list->key_val == NULL)
			msg_error();
		env_list->flag = 1;
		env_list->printed = -1;
		env_list->next = temp;
		temp = env_list;
		i++;
	}
	return  (env_list);
}

//additionally HOME is added for the case if HOME is removed and cd ~ is executed
//flag = 4;
int	add_addit_home(t_env *env)
{
	t_env *new_home;

	new_home = malloc(sizeof(t_env));
	if (!new_home)
		msg_error();
	new_home->next = NULL;
	new_home->flag = 4;
	new_home->printed = -1;
	while (env->next != NULL)
	{
		if (ft_strncmp(env->key_val, "HOME=", 5) == 0)
			new_home->key_val = ft_strdup(env->key_val);
		env = env->next;
	}
	env->next = new_home;
	return (0);
}

int len_arr(char **arr)
{
	int len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}


int	len_lst(t_env *lst)
{
	int		i;
	t_env	*tmp;

	tmp = lst;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++ ;
	}
	return (i);
}

void printfList(t_env *lst) {
	while (lst) {
		printf("%p ", lst);
		printf("%s \n", lst->key_val);
		lst = lst->next;
	}
}

void printArr(char **arr) {
	while (*arr) {
		printf("%s \n", *arr);
		arr++;
	}
}

void 	clean_print_status(t_env *lst)
{
	while (lst)
	{
		lst->printed = -1;
		lst = lst->next;
	}
	
}

//flag 1 = env, 2 = export, 3 = set 
void print_export(t_env *lst)
{
	int		i;
	int		len;
	t_env	*tmp;
	t_env	*min_lst;


	i = 0;
	len = len_lst(lst);
	tmp = lst;
	while (i < len)
	{
		tmp = lst;
		while (tmp->printed >= 0 && tmp->next != NULL)
			tmp = tmp->next;
		min_lst = tmp;
		while (tmp)
		{
			if (ft_strncmp(min_lst->key_val, tmp->key_val, ft_strlen(min_lst->key_val)) > 0 && tmp->printed == -1)
				min_lst = tmp;
			tmp = tmp->next;
		}
		if (min_lst->flag == 1 || min_lst->flag == 2)
			printf("declare -x %s\n", min_lst->key_val);
		min_lst->printed = 1;
		i++;
	}
	clean_print_status(lst);
}

//flag 1 = env, 2 = export, 3 = set, 4 = additional for HOME
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
	if (cmd_flag != 2)
	{
		while (lst)
		{
			if (cmd_flag == 1 && lst->flag == 1)
				printf("%s \n", lst->key_val);
			else if (cmd_flag == 3 && (lst->flag == 1 || lst->flag == 3))
				printf("%s \n", lst->key_val);
			lst = lst->next;
		}
	}
	if (cmd_flag == 2)
		print_export(lst);
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

int	add_new_list(t_env *env, int flag, int printed)
{
	t_env	*env_new;

	env_new = malloc(sizeof(t_env));
	if (env_new == NULL)
	{
		msg_error();
		return (1);
	}
	while (env->next != NULL)
		env = env->next;
	env->next = env_new;
	env_new->next = NULL;
	env_new->flag = flag;
	env_new->printed = printed;
	return (1);
}

