/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:59:10 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:44 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	temp;

	if (ft_memcmp(needle, "", 1) == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (*haystack == *needle)
		{
			temp = len;
			i = 0;
			while (needle[i] && temp)
			{
				if (haystack[i] != needle[i])
					break ;
				if (needle[i + 1] == '\0')
					return ((char *)haystack);
				i++;
				temp--;
			}
		}
		haystack++;
		len--;
	}
	return (NULL);
}
