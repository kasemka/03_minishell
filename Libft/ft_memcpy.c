/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:39 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:57 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_temp;
	char		*dst_origin;
	const char	*src_temp;
	size_t		i;

	if (n == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (dst);
	i = 0;
	dst_origin = dst;
	dst_temp = dst;
	src_temp = src;
	while (i < n)
	{
		dst_temp[i] = src_temp[i];
		i++;
	}
	return (dst_origin);
}
