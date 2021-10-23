/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:58 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:50 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*out;

	if (ft_strlen(s1) == 0)
	{
		out = (char *)malloc(1);
		if (out == NULL)
			return (NULL);
		*out = '\0';
		return (out);
	}
	out = (char *)malloc(ft_strlen(s1) + 1);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, s1, ft_strlen(s1) + 1);
	return (out);
}
