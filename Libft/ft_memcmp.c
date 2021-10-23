/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:38 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:58 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = s1;
	str2 = s2;
	if (n > 0)
	{
		while (n)
		{
			if ((*str1 != *str2) || n == 1)
				break ;
			str1++;
			str2++;
			n--;
		}
		return (*str1 - *str2);
	}
	else
		return (0);
}
