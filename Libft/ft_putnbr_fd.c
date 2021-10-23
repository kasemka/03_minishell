/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:49 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:54 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	power(int val, int power)
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

static void	print_str(int sign, int n, int size, int fd)
{
	unsigned int	temp;
	char			print_me;

	if (sign)
	{
		temp = -n;
		ft_putchar_fd('-', fd);
	}
	else
		temp = n;
	while (temp || size)
	{
		print_me = (temp / (power(10, size - 1))) + '0';
		ft_putchar_fd(print_me, fd);
		temp = temp - power(10, size - 1) * (temp / power(10, size - 1));
		size--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	temp;
	int	size;
	int	sign;

	if (n == 0)
		ft_putchar_fd('0', fd);
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
	print_str(sign, n, size, fd);
}
