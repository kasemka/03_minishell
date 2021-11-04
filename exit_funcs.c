/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:10:02 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 11:10:33 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*exit_failure(t_pipes *pipes, char *out)
{
	t_pipes	*begin;

	free(out);
	while (pipes)
	{
		begin = pipes;
		free_list(pipes->parso);
		pipes = pipes->next;
		free(begin);
	}
	if (!g_exitcode)
	{
		g_exitcode = 1;
		printf("%s\n", strerror(errno));
	}
	return (NULL);
}

void	must_exit_failure(char *err_msg)
{
	if (err_msg)
		exit(errno);
}

void	non_exit_failure(char *err_msg)
{
	if (err_msg)
		perror(err_msg);
	if (errno)
		g_exitcode = errno;
	else
		g_exitcode = 1;
}
