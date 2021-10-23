/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:59:06 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:47 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*temp;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		temp = (char *)malloc(sizeof(char *));
		*temp = '\0';
		return (temp);
	}
	temp = (char *)malloc(ft_strlen(s) + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		temp[i] = f(i, s[i]);
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
