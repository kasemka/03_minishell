#include "minishell.h"

// unset asdf asdfsd HOME - only HOME removed from env
// unset $HOME - if key in env: unset: `/Users/lelle': not a valid identifier.
// unset $COLORFGBG - not a valid identifier
// unset asdf asf - if key not in env: nothing happens
// unset _= - does not work
// unset with asdfasdf= -with "=" not a valid identifier
// unset HOME= - доработать вывод ошибки

void	rm_from_list(t_env **env_list, t_env *env_list_tmp)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (*env_list == env_list_tmp)
		{
			tmp = env_list_tmp->next;
			*env_list = tmp;
		}
		else if (tmp->next == env_list_tmp)
			tmp->next = tmp->next->next;
		if (tmp == env_list_tmp)
		{
			env_list_tmp->next = NULL;
			free(env_list_tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

int	bldin_unset(t_env **env_list, char **args)
{
	int			i;
	int			len;
	t_env		*env_tmp;

	i = 1;
	env_tmp = *env_list;
	while (args[i] != NULL)
	{
		len = ft_strlen(args[i]);
		if (ft_strnstr("_", args[i], len) == NULL)
		{
			while (env_tmp != NULL)
			{
				if (ft_strnstr(env_tmp->key_value, args[i], len) != NULL && \
				ft_strnstr(env_tmp->key_value + len, "=", 1))
				{
					rm_from_list(env_list, env_tmp);
					break ;
				}
				env_tmp = env_tmp->next;
			}
		}
		env_tmp = *env_list;
		i++;
	}
	return (0);
}
