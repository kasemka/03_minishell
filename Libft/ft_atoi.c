/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:03 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 19:00:11 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_isspace(char chr)
{
	if (chr == '\t' || chr == '\n' || chr == '\v')
		return (1);
	else if (chr == '\f' || chr == '\r' || chr == 32)
		return (1);
	else
		return (0);
}

static	int	get_number(const char *str)
{
	int	out;

	out = *str - '0';
	str++;
	while (*str > 47 && *str < 58)
	{
		out = out * 10 + (*str - '0');
		str++;
	}
	return (out);
}

int	ft_atoi(const char *str)
{
	int	sign;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	if (*str > 47 && *str < 58)
		return (get_number(str) * sign);
	return (0);
}
