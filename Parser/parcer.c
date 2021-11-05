/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:13:17 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 21:03:43 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	init_i_start_words(int *s_w_i)
{
	s_w_i[1] = 0;
	s_w_i[2] = -1;
}

char	*parsing_cycle(t_pipes *pipes, char *str, char *out)
{
	int	s_w_i[3];

	init_i_start_words(s_w_i);
	while (str[++s_w_i[2]])
	{
		ft_isspace(str, s_w_i);
		s_w_i[0] = s_w_i[2];
		if (s_w_i[2] == 0 && check_token_errors(str))
			return (NULL);
		while (check_limit_vals(str, s_w_i[2]))
			s_w_i[2]++;
		if (s_w_i[0] != s_w_i[2])
			parser_get_word(&out, str, s_w_i[0], &s_w_i[2]);
		if (str[s_w_i[2]] == '\'' || str[s_w_i[2]] == '\"')
			parser_get_slash(&out, str, &s_w_i[2], pipes);
		if (str[s_w_i[2]] == '$' && (ft_isalnum(str[s_w_i[2] + 1]) \
		|| str[s_w_i[2] + 1] == '?'))
			parser_get_dollar(&out, &s_w_i[2], str, pipes);
		if (str[s_w_i[2]] == ' ' || str[s_w_i[2]] == '\0' || \
			if_pipe_or_redirect(str[s_w_i[2]]))
			parser_get_zero_o_space(&out, &pipes, s_w_i, str);
		if (!out || str[s_w_i[2]] == '\0')
			break ;
	}
	return (out);
}

char	*parser(char *str, t_env *env)
{
	char	*out;
	t_pipes	*pipes;

	pipes = new_pipes(env);
	if (!pipes)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (exit_failure(pipes, NULL));
	if (*str == '\0')
		return ("");
	out = parsing_cycle(pipes, str, out);
	if (!out)
		return (exit_failure(pipes, out));
	g_exitcode = 0;
	make_pipes(pipes);
	free (out);
	free_pipes(pipes);
	return (str);
}
