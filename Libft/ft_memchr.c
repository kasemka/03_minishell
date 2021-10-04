/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:36 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:59 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	chr;
	const char		*str;

	i = 0;
	str = s;
	chr = c;
	while (i < n)
	{
		if ((unsigned char)str[i] == chr)
		{
			str = str + i;
			return ((void *)str);
		}
		i++;
	}
	return (NULL);
}
