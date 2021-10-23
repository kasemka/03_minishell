/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:41 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:57 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cond_moves(char *dst_temp, const char *src_temp, size_t len)
{
	size_t	i;

	i = 0;
	if (dst_temp - src_temp <= 0)
	{
		while (i < len)
		{
			dst_temp[i] = src_temp[i];
			i++;
		}
	}
	else
	{
		while (len >= 1)
		{
			dst_temp[len - 1] = src_temp[len - 1];
			len--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_temp;
	char		*dst_origin;
	const char	*src_temp;

	if (len == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (dst);
	dst_origin = dst;
	dst_temp = dst;
	src_temp = src;
	cond_moves(dst_temp, src_temp, len);
	dst = (void *)dst_temp;
	return (dst_origin);
}
