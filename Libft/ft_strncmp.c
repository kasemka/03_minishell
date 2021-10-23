/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:59:08 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:45 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && n)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2 || n == 1)
			break ;
		s1 += 1;
		s2 += 1;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
