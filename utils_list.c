/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:26:14 by lelle             #+#    #+#             */
/*   Updated: 2021/10/12 14:26:16 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//additionally HOME is added: if HOME is removed and cd ~ is executed
//flag = 4;
int	add_addit_home(t_env *env)
{
	char	*home_addit;

	while (env != NULL)
	{
		if (ft_strncmp(env->key_vl, "HOME=", 5) == 0)
		{
			home_addit = env->key_vl;
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		printf("HOME should be in env before execution!\n");
		exit (1);
	}
	add_new_list(env, 4, -1);
	(last_list(env))->key_vl = ft_strdup(home_addit);
	if ((last_list(env))->key_vl == NULL)
		return (msg_error());
	return (0);
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
			env_list->printed = 0;
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
	{
		msg_error();
		return (1);
	}
	while (env->next != NULL)
		env = env->next;
	env->next = env_new;
	env_new->next = NULL;
	env_new->flg = flag;
	env_new->printed = printed;
	return (1);
}
