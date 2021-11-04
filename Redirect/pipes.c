#include "../ft_minishell.h"

int	pipes_list_size(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (pipes)
	{
		i++;
		pipes = pipes->next;
	}
	return (i);
}

void	close_pipes(t_pipes *pipes)
{
	t_pipes	*dup_pipes;

	dup_pipes = pipes;
	while (pipes)
	{
		if (pipes->fd_in != STD_IN)
			close (pipes->fd_in);
		if (pipes->fd_out != STD_OUT)
			close (pipes->fd_out);
		pipes = pipes->next;
	}
	while (dup_pipes)
	{
		if (dup_pipes->fd_in != STD_IN || dup_pipes->fd_out != STD_OUT)
			waitpid(dup_pipes->pid, 0, 0);
		dup_pipes = dup_pipes->next;
	}
}

void	make_pipes(t_pipes *pipes)
{
	t_pipes	*dup_pipes;

	dup_pipes = pipes;
	while (dup_pipes)
	{
		if (dup_pipes->next)
		{
			pipe(dup_pipes->fd_pipes);
			dup_pipes->fd_out = dup_pipes->fd_pipes[1];
			dup_pipes->next->fd_in = dup_pipes->fd_pipes[0];
		}
		make_redirects(dup_pipes);
		dup_pipes = dup_pipes->next;
	}
	close_pipes(pipes);
}
