/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:16:58 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 20:45:55 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*get_dollar(int *i, char *str, char *out, t_pipes *pipes)
{
	char	*var_val;
	char	*temp1;

	temp1 = out;
	var_val = get_var(str, i, pipes);
	if (var_val)
	{
		out = ft_strjoin(temp1, var_val);
		free(temp1);
		free(var_val);
	}
	return (out);
}

void	parser_get_dollar(char **out, int *i, char *str, t_pipes *pipes)
{
	*out = get_dollar(i, str, *out, pipes);
	(*i)--;
	if (str[*i + 1] == ' ' || str[*i + 1] == '\0')
		(*i)++;
}

void	parser_get_dollar_alone(char **out)
{
	char	*temp1;
	char	*temp;

	temp1 = "$";
	temp = *out;
	*out = ft_strjoin(*out, temp1);
	free (temp);
}
