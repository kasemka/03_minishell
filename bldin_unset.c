/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:27:34 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:52:57 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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
			break ;
		}
		tmp = tmp->next;
	}
	free(env_list_tmp->key_vl);
	free(env_list_tmp);
}

int	bldin_unset(t_env **env_list, char **arg)
{
	int			i;
	int			len;
	t_env		*t;

	i = 0;
	t = *env_list;
	while (arg[++i] != NULL)
	{
		len = ft_strlen(arg[i]);
		if (ft_strnstr("_=", arg[i], len) == NULL)
		{
			while (t != NULL)
			{
				if (ft_strnstr(t->key_vl, arg[i], len) != NULL && \
				ft_strnstr(t->key_vl + len, "=", 1) && t->flg != 4)
				{
					rm_from_list(env_list, t);
					break ;
				}
				t = t->next;
			}
		}
		t = *env_list;
	}
	return (0);
}
