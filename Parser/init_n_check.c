/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:20:20 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 13:22:18 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	if_pipe_or_redirect(char c)
{
	int	i;

	i = 0;
	if (c == '>' || c == '<' || c == '|')
		i = 1;
	return (i);
}

int	check_limit_vals(char *str, int j)
{
	int		i;
	char	c;

	c = str[j];
	i = 0;
	if (c != '\'' && c != '\"' && c != ' ' && c != '\0' \
		&& c != '>' && c != '<' && c != '|')
		i = 1;
	if ((c == '$' && ft_isalnum(str[j + 1])) || \
	(c == '$' && str[j + 1] == '?'))
		i = 0;
	return (i);
}
