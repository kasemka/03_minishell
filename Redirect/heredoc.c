/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:18:15 by lelle             #+#    #+#             */
/*   Updated: 2021/11/04 12:19:37 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	read_2left_arr(int fd_out, char *stop_word)
{
	char	*text_line;
	char	*full_text;
	int		len;

	g_exitcode = 0;
	full_text = NULL;
	while (1)
	{
		text_line = readline("> ");
		len = ft_strlen(text_line);
		if (ft_strncmp(text_line, stop_word, len) == 0)
			break ;
		ft_putendl_fd(text_line, fd_out);
		free(text_line);
	}
}

void	here_doc(t_pipes *pipes, char *stop)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		read_2left_arr(fd[1], stop);
		exit(0);
	}
	waitpid(pid, 0, 0);
	pipes->fd_in = fd[0];
	close(fd[1]);
}
