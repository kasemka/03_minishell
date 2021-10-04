/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:59:13 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:43 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ifzero(void)
{
	char	*out;

	out = (char *)malloc(sizeof(char));
	if (out == NULL)
		return (NULL);
	*out = '\0';
	return (out);
}

int	s_in_set(char s1, char const *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	int		i;
	int		end;

	if (s1 == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ifzero());
	i = 0;
	while (*s1 && s_in_set(*s1, set))
		s1++;
	if (ft_strlen(s1) == 0)
		return (ifzero());
	end = ft_strlen(s1) - 1;
	while (s_in_set(s1[end], set) && end >= 0)
		end--;
	out = (char *)malloc(end + 2);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, s1, end + 2);
	return (out);
}
