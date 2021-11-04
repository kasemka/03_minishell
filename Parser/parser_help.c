/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:23:32 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 11:58:44 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

t_parsing	*new_list(void)
{
	t_parsing	*commons;

	commons = (t_parsing *)malloc(sizeof(t_parsing));
	if (!(commons))
		return (NULL);
	else
	{
		commons->args = NULL;
		commons->next = NULL;
		commons->redirects = NULL;
		commons->real_empty_str = 0;
		return (commons);
	}
}

t_parsing	*find_last(t_parsing *list)
{
	if (!list)
		return (list);
	while (list->next)
		list = list->next;
	return (list);
}

int	parser_list_update(char *out, t_pipes **pipes)
{
	int			flag;
	t_parsing	*last_parso;

	last_parso = find_last((*pipes)->parso);
	flag = 0;
	if (*out != '|')
	{
		last_parso->redirects = ft_strdup(out);
		last_parso->next = new_list();
		if (!((*pipes)->parso->redirects) || !(last_parso->next))
			flag = 1;
	}
	else
	{
		(*pipes)->next = new_pipes((*pipes)->env);
		(*pipes)->next->g_exit = (*pipes)->g_exit;
		if (!((*pipes)->next))
			flag = 1;
		else
			(*pipes) = (*pipes)->next;
	}
	return (flag);
}

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
