/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:59:16 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:36 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ifzero(void)
{
	char	*out;

	out = (char *)malloc(sizeof(char *));
	if (out == NULL)
		return (NULL);
	*out = '\0';
	return (out);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	max;

	if (s == NULL)
		return (NULL);
	max = len + 1;
	if (max > ft_strlen(s))
		max = ft_strlen(s);
	if (start >= ft_strlen(s) || len == 0)
		return (ifzero());
	out = (char *)malloc(max);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		out[i] = s[start];
		i++;
		start++;
	}
	if (out[i - 1] != '\0')
		out[i] = '\0';
	return (out);
}
