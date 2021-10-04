/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:13:17 by gvolibea          #+#    #+#             */
/*   Updated: 2021/10/04 22:18:25 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

void init_i_start_words(int *i, int *start_words_num)
{
	*i = -1;
	start_words_num[1] = 0;
}

char *parsing_cycle(t_parsing *parso, char *str, char *out)
{
	int i;
	int start_words_num[2];

	init_i_start_words(&i, start_words_num);
	while (str[++i])
	{
		ft_isspace(&str);
		start_words_num[0] = i;
		while((str[i] != '\'' && str[i] != '\"' && str[i] != ' ' \
			&& str[i] != '$') && str[i])
			i++;
		if (start_words_num[0] != i)
			parser_get_word(&out, str, start_words_num[0], &i);
		if (str[i] ==  '\'' || str[i] ==  '\"')
			parser_get_slash(&out, str, &i);
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
			parser_get_dollar(&out, &i, str);
		else if (str[i] == '$')
			parser_get_dollar_alone(&out);
		if (str[i] == ' ' || str[i] == '\0' || str[i] == '|')
			parser_get_zero_o_space(&out, &parso, &start_words_num[1]);
		if (!out || str[i] == '\0')
			break ;
	}
	return (out);
}

char *parser(char *str)
{
	char *out;
	t_parsing *parso;

	parso = new_list();
	if (!parso)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		exit_failure(parso, NULL);
	if (*str == '\0')
		return ("");
	out = parsing_cycle(parso, str, out);
	if (!out)
		return (exit_failure(parso, out));
	print_list(parso);
	free_list(parso);
	return (str);
}

int main(int argc, char **argv, char **env)
{
	char *test;

	while (1)
	{
		test = readline(SHL_NAME);
		add_history(test);
		parser(test);
	}
	return (1);
}
