/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:26:24 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:58:47 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	msg_error_str(char *s)
{
	printf("%s: %s\n", s, strerror(errno));
	return (errno);
}

int	msg_error(void)
{
	printf("%s\n", strerror(errno));
	return (errno);
}

int	msg_mallocfail(void)
{
	printf("Cannot allocate memory.\n");
	return (12);
}

int	msg_home_not_set(void)
{
	printf("cd: HOME not set\n");
	return (1);
}
