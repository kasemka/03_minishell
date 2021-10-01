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
	new_list->key_val = ft_strdup(key_value);
	if (new_list->key_val == NULL)
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
	free(env_list_tmp->key_val);
	if (ft_strncmp(key_value, "_", 2) == 0)
		env_list_tmp->key_val = ft_strdup("_=env");
	else
		env_list_tmp->key_val = ft_strdup(key_value);
	if (env_list_tmp->key_val == NULL)
		msg_error();
}

int	bldin_export(t_env **env, char **arg)
{
	int			i;
	int			len;
	t_env		*tmp;

	i = 0;
	tmp = *env;
	if (arg[1] == NULL)
		print_env(*env, arg[0]);
	while (arg[++i] != NULL)
	{
		len = len_before_equal(arg[i]);
		while (tmp)
		{
			if (ft_strncmp(tmp->key_val, arg[i], len) == 0 && len && tmp->flag != 4)
			{
				change_env(tmp, arg[i]);
				break ;
			}
			tmp = tmp->next;
		}
		if (tmp == NULL)
			add_env(*env, arg[i], arg[0]);
		tmp = *env;
	}
	return (0);
}
