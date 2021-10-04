/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:59 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:50 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_str(char *str, char *src, int pos)
{
	str = str + pos;
	while (*src)
	{
		*str = *src;
		str++;
		src++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*out;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 == 0 && len_s2 == 0)
	{
		out = (char *)malloc(1);
		if (out == NULL)
			return (NULL);
		*out = '\0';
		return (out);
	}
	out = (char *)malloc(len_s2 + len_s1 + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	fill_str(out, (char *)s1, 0);
	fill_str(out, (char *)s2, len_s1);
	out[len_s1 + len_s2] = '\0';
	return (out);
}
