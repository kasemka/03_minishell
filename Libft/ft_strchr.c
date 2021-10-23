/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:56 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:51 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	chr;

	chr = c;
	if (chr == '\0')
	{
		s += ft_strlen(s);
		return ((char *)s);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == chr)
		{
			s = s + i;
			return ((char *)s);
		}
		i++;
	}
	return (NULL);
}
