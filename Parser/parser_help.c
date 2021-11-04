/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:23:32 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 12:11:32 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*get_pipe_o_redirect(char *str, int *s_w_i)
{
	if (str[s_w_i[2]] == '|')
		return ("|");
	if (str[s_w_i[2]] == '>')
	{
		if (str[s_w_i[2] + 1] == '>')
		{
			s_w_i[2]++;
			return (">>");
		}
		return (">");
	}
	if (str[s_w_i[2]] == '<')
	{
		if (str[s_w_i[2] + 1] == '<')
		{
			s_w_i[2]++;
			return ("<<");
		}
		return ("<");
	}
	return (NULL);
}

void	parser_get_zero_o_space(char **out, t_pipes **pipes, int *s_w_i, \
	char *str)
{
	int			flag;
	char		*temp;
	t_parsing	*last_parso;

	flag = 0;
	if ((!pipe_o_redirect(*out) && ft_strncmp(*out, "", 1)) || \
		(!ft_strncmp(*out, "", 1) && (*pipes)->parso->real_empty_str))
	{
		(s_w_i[1])++;
		last_parso = find_last((*pipes)->parso);
		last_parso->args = add_array_element(last_parso, *out, s_w_i[1]);
		if (!last_parso->args)
			flag = 1;
	}
	if (pipe_o_redirect(*out) || if_pipe_or_redirect(str[s_w_i[2]]))
	{
		temp = *out;
		if (if_pipe_or_redirect(str[s_w_i[2]]))
			temp = get_pipe_o_redirect(str, s_w_i);
		flag = parser_list_update(temp, pipes);
		s_w_i[1] = 0;
	}
	free(*out);
	(*pipes)->parso->real_empty_str = 0;
	if (flag)
		*out = NULL;
	if (*out)
		*out = ft_strdup("");
}
