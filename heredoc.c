/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:18:15 by lelle             #+#    #+#             */
/*   Updated: 2021/10/26 19:07:11 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void read_2left_arr(int fd_out, char *stop_word)
{
	char	*text_line;
	char	*full_text;
	int		len;

	g_exitcode = 0;
	len = ft_strlen(stop_word);
	full_text = NULL;
	while (1)
	{
		text_line = readline("< ");
		if (ft_strncmp(text_line, stop_word, len) == 0)
			break ;
		if (!full_text)
			full_text = ft_strdup(text_line);
		else
			full_text = ft_strjoin(full_text, text_line);
		if (!full_text)
		{
			g_exitcode = msg_mallocfail();
			break ;
		}
		free(text_line);
	}
	printf("%s", full_text);
	if (*full_text)
		free(full_text);
	if (*text_line)
		free(text_line);
//	return (g_exitcode);
}
