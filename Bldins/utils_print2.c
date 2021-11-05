/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:26:24 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:58:47 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	msg_mallocfail(void)
{
	ft_putstr_fd("Cannot allocate memory.\n", STDERR_FILENO);
	return (12);
}

char	*msg_mallocfail_null(void)
{
	ft_putstr_fd("Cannot allocate memory.\n", STDERR_FILENO);
	return (NULL);
}
