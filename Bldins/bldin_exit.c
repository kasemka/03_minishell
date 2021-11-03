/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:17 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:52:53 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	is_num(char *s)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (ft_isdigit(*s) == 1)
			s++;
		else
			return (0);
	}
	return (1);
}

int	bldin_exit(char **args)
{
	(void)args;
	g_exitcode = 0;
	if (args[1] == NULL)
		exit(g_exitcode);
	else if (is_num(args[1]) == 0)
	{
		ft_putstr_fd("exit\nminishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_exitcode = 255;
	}
	else if (args[2] != NULL)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_exitcode = 1;
		return (1);
	}
	else if (is_num(args[1]) == 1)
		g_exitcode = ft_atoi(args[1]);
	exit(g_exitcode);
}
