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

void make_pipes(t_pipes *pipes)
{
	// get len_of_pipes_list
	// if len_of_pipes_list > 1
		// fd_pipe = make pipes array int **fd (size of list x sizeof(*int))
		// pipes (fd_pipe)
	// cycle throght pipes lists (even if no)
	// --
		// if pipes
			// change file descriptors acc to new_pipes - do open / close
		// launch execution
		// list++;
	// --

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
}
