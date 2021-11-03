/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:18:15 by lelle             #+#    #+#             */
/*   Updated: 2021/11/03 16:52:25 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void read_2left_arr(int fd_out, char *stop_word)
{
	char	*text_line;
	char	*full_text;
	int		len;

	(void)fd_out;
	g_exitcode = 0;
	len = ft_strlen(stop_word);
	full_text = NULL;
	while (1)
	{
		text_line = readline("> ");
		if (ft_strncmp(text_line, stop_word, len) == 0)
			break ;
		ft_putendl_fd(text_line, fd_out);
		//write(fd_out, text_line, ft_strlen(text_line));
		/*if (!full_text)
			full_text = ft_strdup(text_line);
		else
			full_text = ft_strjoin(full_text, text_line);
		if (!full_text)
		{
			g_exitcode = msg_mallocfail();
			break ;
		}*/
		free(text_line);
	}
	/*printf("%s", full_text);
	if (*full_text)
		free(full_text);
	if (*text_line)
		free(text_line);*/
	// return (g_exitcode);
}

void here_doc(t_pipes *pipes, char *stop)
{
	int fd[2];
	pid_t pid;
	(void)pipes;
	// in parent process get change_shlvl

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		read_2left_arr(fd[1], stop);
		//close(fd[1]);
		exit(0);
	}
	// in child process readline
	waitpid(pid,0,0);
	pipes->fd_in = fd[0];
	close(fd[1]);
	//close(fd[1]);

//	close(fd[0]);

}
