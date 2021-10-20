/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:27:46 by lelle             #+#    #+#             */
/*   Updated: 2021/10/12 14:27:48 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bldin_pwd(void)
{
	char	*buf;
	size_t	size;

	size = 4096;
	buf = malloc(size * sizeof(char));
	if (buf == NULL)
		msg_mallocfail();
	printf("%s\n", getcwd(buf, size));
	free(buf);
	return (0);
}
