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

int	bldin_echo(char **args)
{
	int		i;

	i = 0;
	if (ft_strncmp(args[1], "-n", 3) == 0)
		i++;
	while (args[++i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
	}
	if (ft_strncmp(args[1], "-n", 3) != 0)
		printf("\n");
	return (0);
}
