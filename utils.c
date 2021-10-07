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



char *find_by_key(t_env *env, char *key_env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key_val, key_env, ft_strlen(key_env)) == 0 &&\
		env->key_val[ft_strlen(key_env)] == '=')
			return (env->key_val);
		env = env->next;
	}
	return (NULL);
}
