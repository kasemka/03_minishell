/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:27:46 by lelle             #+#    #+#             */
/*   Updated: 2021/11/01 16:20:23 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	bldin_pwd(t_env *env)
{
	char	*buf;
	size_t	size;

	size = 4096;
	buf = malloc(size * sizeof(char));
	if (buf == NULL)
		return (msg_mallocfail());
	getcwd(buf, size);
	if (!buf)
	{
		while (ft_strncmp(env->key_vl, "PWD=", 4) != 0 && env->flg != 4)
			env = env->next;
		ft_putstr_fd(env->key_vl + 4, STD_OUT);
	}
	else
		printf("%s\n", buf);
	free(buf);
	return (0);
}
