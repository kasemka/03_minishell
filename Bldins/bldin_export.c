/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:05 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:52:54 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

//flag 1 = env, 2 = export, 4 = additional
int	add_env(t_env *env, char *key_value)
{
	t_env	*new_list;

	new_list = env;
	if (add_new_list(env, 0, -1) != 0)
		return (errno);
	while (new_list->next != NULL)
		new_list = new_list->next;
	if (ft_strnstr(key_value, "+=", 3))
		new_list->key_vl = ft_strjoin(ft_substr(key_value, 0, \
		len_key(key_value)), key_value + len_key(key_value) + 1);
	else
		new_list->key_vl = ft_strdup(key_value);
	if (new_list->key_vl == NULL)
		return (errno);
	if (ft_strchr(key_value, '=') != NULL)
		new_list->flg = 1;
	else
		new_list->flg = 2;
	return (0);
}

int	change_value(t_env *env, char *key_vl)
{
	char	*new_vl;
	char	*old_vl;

	old_vl = key_vl;
	new_vl = NULL;
	if (!ft_strncmp(key_vl, "_=", 2) || !ft_strncmp(key_vl, "_+=", 3))
		return (0);
	else if (key_vl[len_key(key_vl)] == '+')
	{
		new_vl = ft_strjoin(env->key_vl, (key_vl + len_key(key_vl) + 2));
		if (new_vl != NULL)
			env->key_vl = new_vl;
	}
	else
		env->key_vl = ft_strdup(key_vl);
	if (env->key_vl == NULL)
		return (errno);
	return (0);
}

int	change_env(t_env *env, char **arg)
{
	int			i;
	int			len;
	t_env		*t;

	i = 0;
	while (arg[++i] != NULL)
	{
		t = env;
		len = len_key(arg[i]);
		while (t)
		{
			if (((ft_strncmp(t->key_vl, arg[i], len) == 0 && len) || \
			ft_strncmp(t->key_vl, arg[i], ft_strlen(arg[i])) == 0) \
			&& t->flg != 4)
			{
				if (change_value(t, arg[i]) == 12)
					return (12);
				break ;
			}
			t = t->next;
		}
		if (t == NULL && !check_name(arg[i]) && add_env(env, arg[i]) == 12)
			return (12);
	}
	return (0);
}

int	bldin_export(t_env **env, char **arg)
{
	int			status;

	status = 0;
	if (arg[1] == NULL)
		print_env(*env, arg[0]);
	else
		status = change_env(*env, arg);
	if (status == 12)
		msg_mallocfail();
	return (status);
}
