/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:35 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:59 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	chr;
	char			*dst_temp;
	const char		*src_temp;
	size_t			i;

	chr = c;
	i = 0;
	dst_temp = dst;
	src_temp = src;
	while (i < n)
	{
		dst_temp[i] = src_temp[i];
		if ((unsigned char)src_temp[i] == chr)
		{
			dst_temp = dst_temp + i + 1;
			dst = dst_temp;
			return (dst);
		}
		i++;
	}
	return (NULL);
}
