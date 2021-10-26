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

void execution(t_pipes *pipes)
{
	//  execution
	// ++
		// launch redirects (break pipes in case is necessary)

		// if fd_in or fd_out differs -  is_fork
		// if fork
			//run comand in child
		// else
			// wait for fork
		// else
			// run comand
	//++
	make_redirects(pipes);
}

void make_pipes(t_pipes *pipes)
{
	// cycle throght pipes lists (even if no)
	// --
		// if pipes->next
			// make pipe command
		// launch execution
		// list++;
	// --
	t_pipes *dup_pipes;

	dup_pipes = pipes;
	while (dup_pipes)
	{
		if (dup_pipes->next)
		{
			// make new fd_s and pipe
			pipe(dup_pipes->fd_pipes);
			dup_pipes->fd_out = dup_pipes->fd_pipes[1];
			dup_pipes->next->fd_in = dup_pipes->fd_pipes[0];
			//printf("pipe add is %d",dup_pipes->next->fd_in);
		}
		execution(dup_pipes);
		dup_pipes = dup_pipes->next;
	}
}
