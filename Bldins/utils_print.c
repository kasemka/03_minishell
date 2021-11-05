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
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (errno);
}

int	msg_error(void)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (errno);
}

int	msg_home_not_set(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (1);
}

int	msg_error_export(char *s)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	g_exitcode = 1;
	return (1);
}

int	msg_minsh_str(char *cmd, char *err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (*err)
	{
		ft_putstr_fd(err, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (errno);
}
