#include "minishell.h"

// unset asdf asdfsd HOME - only HOME removed from env
// unset $HOME - if key in env: unset: `/Users/lelle': not a valid identifier.
// unset $COLORFGBG - not a valid identifier
// unset asdf asf - if key not in env: nothing happens
// unset _= - does not work
// unset with asdfasdf= -with "=" not a valid identifier
// unset HOME= - доработать вывод ошибки

void	rm_from_list(t_env *env_list, int i)
{
	int		j;
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*free_old;

	tmp = env_list;
	tmp2 = env_list;
	j = 0;
	while (j <= i)
	{
		if (j == i)
		{
			tmp2 = tmp2->next;
			tmp->next = NULL;
			*env_list = *tmp2;
			break ;
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

int	unset(t_env *env_list, char *key)
{
	int		len;
	int		i;
	t_env	*env_list_tmp;

	i = 0;
	env_list_tmp = env_list;
	len = ft_strlen(key);
	if (ft_strnstr("_", key, len) != NULL)
		return (1);
	while (env_list_tmp != NULL)
	{
		if (ft_strnstr(env_list_tmp->key_value, key, len) != NULL && \
		ft_strnstr(env_list_tmp->key_value + len, "=", 1))
		{
			rm_from_list(env_list, i);
			break ;
		}
		env_list_tmp = env_list_tmp->next;
		i++;
	}
	return (0);
}

int	bldin_unset(t_env *env_list, char **commands)
{
	int	i;

	i = 1;
	while (commands[i] != NULL)
	{
		unset(env_list, commands[i]);
		i++;
	}
	return (0);
}
