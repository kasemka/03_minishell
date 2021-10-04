/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:31 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 19:00:00 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	power(int val, int power)
{
	int				out;

	out = 1;
	if (power == 0)
		return (1);
	else if (power == 1)
		return (val);
	while (power >= 1)
	{
		out *= val;
		power--;
	}
	return (out);
}

static void	get_str(int sign, char *out, int n, int size)
{
	unsigned int	temp;

	if (sign)
	{
		temp = -n;
		*out = '-';
		out++;
	}
	else
		temp = n;
	while (temp || size)
	{
		*out = (temp / (power(10, size - 1))) + '0';
		temp = temp - power(10, size - 1) * (temp / power(10, size - 1));
		size--;
		out++;
	}
	*out = '\0';
}

static char	*ifzero(void)
{
	char			*out;

	out = (char *)malloc(2);
	if (out == NULL)
		return (NULL);
	out[0] = '0';
	out[1] = '\0';
	return (out);
}

char	*ft_itoa(int n)
{
	char			*out;
	int				size;
	int				temp;
	int				sign;

	if (n == 0)
		return (ifzero());
	sign = 0;
	if (n < 0)
		sign = 1;
	temp = n;
	size = 0;
	while (temp)
	{
		temp /= 10;
		size++;
	}
	out = (char *)malloc(size + 1 + sign);
	if (out == NULL)
		return (NULL);
	get_str(sign, out, n, size);
	return (out);
}
