/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:05 by lelle             #+#    #+#             */
/*   Updated: 2021/10/12 14:25:08 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//flag 1 = env, 2 = export, 3 = set 
int	add_env(t_env *env, char *key_value, char *cmd)
{
	t_env	*new_list;
	int		is_set;

	new_list = env;
	is_set = 0;
	if (ft_strncmp(cmd, "set_local", 10) == 0)
		is_set = 1;
	add_new_list(env, 0, -1);
	while (new_list->next != NULL)
		new_list = new_list->next;
	if (ft_strnstr(key_value, "+=", 2) == 0)
		new_list->key_vl = ft_strjoin(ft_substr(key_value, 0, \
		len_key(key_value)), key_value + len_key(key_value) + 1);
	else
		new_list->key_vl = ft_strdup(key_value);
	if (new_list->key_vl == NULL)
		return (msg_error());
	if (ft_strchr(key_value, '=') != NULL && is_set == 0)
		new_list->flg = 1;
	else if (ft_strchr(key_value, '=') != NULL && is_set == 1)
		new_list->flg = 3;
	else
		new_list->flg = 2;
	return (0);
}

void	change_env(t_env *env, char *key_vl)
{
	char	*new_vl;
	char	*old_vl;

	old_vl = key_vl;
	new_vl = NULL;
	if (ft_strncmp(key_vl, "_=", 2) == 0 || ft_strncmp(key_vl, "_+=", 3) == 0)
		env->key_vl = ft_strdup("_=env");
	else if (key_vl[len_key(key_vl)] == '+')
	{
		new_vl = ft_strjoin(env->key_vl, (key_vl + len_key(key_vl) + 2));
		if (new_vl != NULL)
			env->key_vl = new_vl;
	}
	else
		env->key_vl = ft_strdup(key_vl);
	if (env->key_vl == NULL)
		msg_error();
	free(old_vl);
}

int	bldin_export(t_env **env, char **arg)
{
	int			i;
	int			len;
	t_env		*t;

	i = 0;
	if (arg[1] == NULL)
		print_env(*env, arg[0]);
	while (arg[++i] != NULL)
	{
		t = *env;
		len = len_key(arg[i]);
		while (t)
		{
			if (((!ft_strncmp(t->key_vl, arg[i], len) && \
			t->key_vl[len] == '=' && len) || ft_strncmp(t->key_vl, arg[i], \
			!ft_strlen(arg[i]))) && t->flg != 4)
			{
				change_env(t, arg[i]);
				break ;
			}
			t = t->next;
		}
		if (t == NULL && !check_export_name(arg[i]))
			add_env(*env, arg[i], arg[0]);
	}
	return (0);
}
