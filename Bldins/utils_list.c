/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:26:14 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:58:44 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	len_lst(t_env *lst, int flag)
{
	int		i;
	t_env	*tmp;

	tmp = lst;
	i = 0;
	while (tmp != NULL)
	{
		if (flag == 0)
			i++ ;
		if (flag && tmp->flg == flag)
			i++ ;
		tmp = tmp->next;
	}
	return (i);
}

//change code after malloc error!!!!!!!!!!!!!!!!!!!!!!!!!!
t_env	*arr_to_list(char **envp, int env_len)
{
	t_env	*temp;
	t_env	*env_list;

	temp = NULL;
	while (env_len-- > 0)
	{
		env_list = malloc(sizeof(t_env));
		if (!env_list)
			msg_mallocfail();
		env_list->key_vl = ft_strdup(envp[env_len]);
		if (env_list->key_vl == NULL)
			msg_mallocfail();
		env_list->flg = 1;
		if (ft_strncmp(env_list->key_vl, "_=", 2) != 0)
			env_list->printed = -1;
		else
		{
			env_list->printed = 0;
			free(env_list->key_vl);
			env_list->key_vl = ft_strdup("_=env");
		}
		env_list->next = temp;
		temp = env_list;
	}
	return (env_list);
}

t_env	*last_list(t_env *env)
{
	while (env->next != NULL)
		env = env->next;
	return (env);
}

int	add_new_list(t_env *env, int flag, int printed)
{
	t_env	*env_new;

	env_new = malloc(sizeof(t_env));
	if (env_new == NULL)
		return (msg_mallocfail());
	while (env->next != NULL)
		env = env->next;
	env->next = env_new;
	env_new->next = NULL;
	env_new->flg = flag;
	env_new->printed = printed;
	return (0);
}
