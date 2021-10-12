/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:17 by lelle             #+#    #+#             */
/*   Updated: 2021/10/12 14:25:20 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// exit | echo "how" - exit ignored
// echo "how" | exit - both ignored
// exit asd - works but with error
// between 0 and 255
// Other numbers can be used, but these are treated modulo 256, 
// so exit -10 is equivalent to exit 246, 
// and exit 257 is equivalent to exit 1.
// change SHLVL in env??? probably later
// exit * asd"
int	bldin_exit(char **args)
{
	(void)args;
	if (is_num(args[1]) == 0)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", args[1]);
		g_exitcode = 255;
	}
	else if (args[2] != NULL)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		g_exitcode = 1;
		return (1);
	}
	else if (is_num(args[1]) == 1)
		g_exitcode = ft_atoi(args[1]);
	exit(g_exitcode);
}
