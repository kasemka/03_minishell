/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:59:11 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:44 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	chr;
	int		pos;

	chr = c;
	if (chr == '\0')
	{
		s += ft_strlen(s);
		return ((char *)s);
	}
	i = 0;
	pos = -1;
	while (s[i])
	{
		if (s[i] == chr)
			pos = i;
		i++;
	}
	if (pos > -1)
	{
		s = s + pos;
		return ((char *)s);
	}
	return (NULL);
}
