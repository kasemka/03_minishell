/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:26:00 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:54:13 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	len_arr(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

char	**list_to_arr(t_env *env)
{
	char	**arr;
	int		i;

	i = -1;
	arr = malloc((len_lst(env, 1) + 1) * sizeof(char *));
	if (!arr)
		return (0);
	while (env != NULL)
	{
		if (env->flg == 1)
		{
			arr[++i] = ft_strdup(env->key_vl);
			if (arr[i] == NULL)
			{
				while (i-- >= 0)
					free(arr[i]);
				free(arr);
				exit(msg_mallocfail());
			}
		}
		env = env->next;
	}
	arr[++i] = NULL;
	return (arr);
}
