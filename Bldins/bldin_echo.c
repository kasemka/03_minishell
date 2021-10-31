/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:29 by lelle             #+#    #+#             */
/*   Updated: 2021/10/24 12:52:19 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	is_newline(char *nl)
{
	if (*nl != '-')
		return (0);
	nl++;
	while (*nl != '\0')
	{
		if (*nl != 'n')
			return (0);
		nl++;
	}
	return (1);
}

int	bldin_echo(char **args)
{
	int		i;

	i = 0;
	if (args[1] == NULL)
	{
	 	ft_putstr_fd("\n", STDIN_FILENO);
		return (0);
	}
	if (is_newline(args[1]) == 1)
		i++;
	while (args[++i] != NULL)
	{
		ft_putstr_fd(args[i], STDIN_FILENO);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", STDIN_FILENO);
	}
	if (is_newline(args[1]) == 0)
		ft_putstr_fd("\n", STDIN_FILENO);
	return (0);
}
