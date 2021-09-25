#include "minishell.h"

// HOME=5555
// arg="2 3 1"
// check key value includes only char + digit+ _
// export 12HOME=asdf

//flag 1 = env, 2 = export, 3 = set 
int	add_env(t_env *env_list, char *key_value, char *cmd)
{
	t_env	*new_list;
	int		is_set;

	is_set = 0;
	if (ft_strncmp(cmd, "set_local", 10) == 0)
		is_set = 1;
	if (check_export_name(key_value) == 1)
		return (1);
	new_list = malloc(sizeof(t_env));
	if (new_list == NULL)
		msg_error();
	while (env_list->next != NULL)
		env_list = env_list->next;
	env_list->next = new_list;
	new_list->next = NULL;
	new_list->key_value = ft_strdup(key_value);
	if (new_list->key_value == NULL)
		msg_error();
	if (ft_strchr(key_value, '=') != NULL && is_set == 0)
		new_list->flag = 1;
	else if (ft_strchr(key_value, '=') != NULL && is_set == 1)
		new_list->flag = 3;
	else 
		new_list->flag = 2;
	return (0);
}

void	change_env(t_env *env_list_tmp, char *key_value)
{
	// int		i;

	// i = 0;
	free(env_list_tmp->key_value);
	if (ft_strncmp(key_value, "_", 2) == 0)
		env_list_tmp->key_value = ft_strdup("_=env");
	else
		env_list_tmp->key_value = ft_strdup(key_value);
	if (env_list_tmp->key_value == NULL)
		msg_error();
}

int	bldin_export(t_env **env_list, char **args)
{
	int			i;
	int			len;
	t_env		*env_tmp;

	i = 0;
	env_tmp = *env_list;
	if (args[1] == NULL)
		print_env(*env_list, args[0]);
	while (args[++i] != NULL)
	{
		len = len_before_equal(args[i]);
		while (env_tmp)
		{
			if (ft_strncmp(env_tmp->key_value, args[i], len) == 0 && len)
			{
				change_env(env_tmp, args[i]);
				break ;
			}
			env_tmp = env_tmp->next;
		}
		if (env_tmp == NULL)
			add_env(*env_list, args[i], args[0]);
		env_tmp = *env_list;
	}
	return (0);
}
