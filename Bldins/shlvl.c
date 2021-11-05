/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:50:22 by lelle             #+#    #+#             */
/*   Updated: 2021/11/05 12:50:25 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	change_shlvl(t_env *env)
{
	int		level;
	char	*lev_char;

	level = 0;
	env = find_by_key(env, "SHLVL");
	if (env)
	{
		if (ft_strncmp(env->key_vl, "SHLVL=", 7) != 0)
			level = ft_atoi(env->key_vl + 6);
		free(env->key_vl);
		if (level < 999)
		{
			level++;
			lev_char = ft_itoa(level);
			if (lev_char == NULL)
				exit (msg_mallocfail());
			env->key_vl = ft_strjoin("SHLVL=", lev_char);
			free(lev_char);
		}
		else
			env->key_vl = ft_strdup("SHLVL=");
		if (env->key_vl == NULL)
			exit (msg_mallocfail());
	}
}
