/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:17 by lelle             #+#    #+#             */
/*   Updated: 2021/11/05 10:02:48 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	if_not_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (1);
		s++;
	}
	return (0);
}

int	is_num(char *s)
{
	char	*max_num;

	max_num = "9223372036854775807";
	if (s == NULL)
		return (0);
	if (*s == '-')
		s++;
	if (if_not_digit(s))
		return (0);
	if (ft_strlen(s) < ft_strlen(max_num))
		return (1);
	if (ft_strncmp(s, max_num, ft_strlen(s)))
		return (0);
	return (1);
}

int	bldin_exit(char **args)
{
	(void)args;
	g_exitcode = 0;
	if (args[1] == NULL)
	{
		ft_putstr_fd("exit\n", STD_IN);
		exit(g_exitcode);
	}
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
