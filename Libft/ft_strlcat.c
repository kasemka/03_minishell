/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:59:01 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:49 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_size;
	size_t	src_size;

	src_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	if (dstsize <= dst_size)
		return (src_size + dstsize);
	i = dst_size;
	while (i < dstsize - 1 && src[i - dst_size])
	{
		dst[i] = src[i - dst_size];
		i++;
	}
	dst[i] = '\0';
	return (src_size + dst_size);
}
