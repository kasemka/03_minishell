#include "minishell.h"

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

t_env	*last_list(t_env *env)
{
	while (env->next != NULL)
		env = env->next;
	return (env);
}
