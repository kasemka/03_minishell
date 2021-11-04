#include "../ft_minishell.h"

void	check_heredocs(t_pipes *pipes)
{
	t_parsing	*begin;

	begin = pipes->parso;
	while (begin)
	{
		if (begin->redirects)
		{
			if (!ft_strncmp(begin->redirects, "<<", 2))
				here_doc(pipes, begin->next->args[0]);
		}
		begin = begin->next;
	}
}

char	**update_allargs(t_pipes *pipes, char **all_args)
{
	t_parsing	*begin;

	begin = pipes->parso;
	while (begin)
	{
		all_args = update_array(all_args, pipes, begin);
		begin = begin->next;
		if (!all_args)
			break ;
	}
	return (all_args);
}

void	make_forks(t_pipes *pipes, char **all_args)
{
	pipes->fork = 0;
	pipes->pid = 0;
	if ((pipes->fd_in != STD_IN || pipes->fd_out != STD_OUT) && !g_exitcode)
	{
		pipes->pid = fork();
		pipes->fork = 1;
	}
	if (!pipes->fork && !g_exitcode)
		run_commands(all_args, pipes);
	if (!pipes->pid && !g_exitcode && pipes->fork)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(pipes->fd_in, STD_IN);
		dup2(pipes->fd_out, STD_OUT);
		if (pipes->next)
			close(pipes->next->fd_in);
		run_commands(all_args, pipes);
		if (pipes->fd_in != STD_IN || pipes->fd_out != STD_OUT)
			exit(g_exitcode);
	}
}

int	make_redirects(t_pipes *pipes)
{
	char	**all_args;

	all_args = NULL;
	check_heredocs(pipes);
	all_args = update_allargs(pipes, all_args);
	make_forks(pipes, all_args);
	if (pipes->fd_in != STD_IN)
		close (pipes->fd_in);
	if (pipes->fd_out != STD_OUT)
		close (pipes->fd_out);
	if (pipes->pid < 0)
		non_exit_failure("minishell: fork: ");
	if (!pipes->next && !g_exitcode)
	{
		waitpid(pipes->pid, &pipes->stat_loc, 0);
		print_row(pipes->stat_loc);
	}
	clean_array(all_args);
	if (pipes->next)
		g_exitcode = 0;
	return (0);
}
