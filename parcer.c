/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:13:17 by gvolibea          #+#    #+#             */
/*   Updated: 2021/10/23 15:52:51 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

void init_i_start_words(int *s_w_i)
{
	s_w_i[1] = 0;
	s_w_i[2] = -1;
}

/*void parse_pipe_inside(char *str,int i)
{
	if
}*/

int check_limit_vals(char c)
{
	int i;

	i = 0;
	if (c != '\'' && c != '\"' && c != ' ' && c != '$'  && c != '\0' \
		&& c != '>' && c != '<' && c != '|')
		i = 1;
	return (i);
}

int if_pipe_or_redirect(char c)
{
	int i;

	i = 0;
	if (c == '>' || c == '<' || c == '|')
		i = 1;
	return (i);

}

char *parsing_cycle(t_pipes *pipes, char *str, char *out)
{
	int s_w_i[3];

	init_i_start_words(s_w_i);
	while (str[++s_w_i[2]])
	{
		ft_isspace(str, s_w_i);
		s_w_i[0] = s_w_i[2];
		while(check_limit_vals(str[s_w_i[2]]))
			s_w_i[2]++;
		if (s_w_i[0] != s_w_i[2])
			parser_get_word(&out, str, s_w_i[0], &s_w_i[2]);
		if (str[s_w_i[2]] ==  '\'' || str[s_w_i[2]] ==  '\"')
			parser_get_slash(&out, str, &s_w_i[2], pipes->parso);
		if (str[s_w_i[2]] == '$' && (ft_isalnum(str[s_w_i[2] + 1]) \
		|| str[s_w_i[2] + 1] == '?'))
			parser_get_dollar(&out, &s_w_i[2], str);
		else if (str[s_w_i[2]] == '$')
			parser_get_dollar_alone(&out);
		if (str[s_w_i[2]] == ' ' || str[s_w_i[2]] == '\0' || \
			if_pipe_or_redirect(str[s_w_i[2]]))
			parser_get_zero_o_space(&out, &pipes, s_w_i, str);
		if (!out || str[s_w_i[2]] == '\0')
			break ;
	}
	return (out);
}

t_pipes *new_pipes(void)
{
	t_pipes		*new_pipe;
	t_parsing	*new_parso;

	new_pipe = malloc(sizeof(t_pipes));
	new_parso = new_list();
	new_pipe->parso = new_parso;
	new_pipe->next = NULL;
	new_pipe->fd_in = STD_IN;
	new_pipe->fd_out = STD_OUT;
	return (new_pipe);
}

char *parser(char *str)
{
	char *out;
//	t_parsing *parso;

	//parso = new_list();
	t_pipes *pipes;
	pipes = new_pipes();
	if (!pipes)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		exit_failure(pipes, NULL);
	if (*str == '\0')
		return ("");
	out = parsing_cycle(pipes, str, out);
	if (!out)
		return (exit_failure(pipes, out));
	//print_list(pipes);
	make_pipes(pipes);
	free (out);
	free_pipes(pipes);
	return (str);
}

// make funck here to read from terminal

// make func to send parso after reading str for next procedures

// do tasks with redirects
	// check if it is available
	// create file acc to it's type
	// update arguments array with args following after filenames
	// exit on strerror'
	// execute initial program with arguments available



int main(int argc, char **argv, char **env)
{
	char *test;
	// add env into structure (or to parso)


	while (1)
	{
		test = readline(SHL_NAME);
		add_history(test);
		parser(test);
	//	while(1);
	}
	return (1);
}
