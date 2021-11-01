#include "../ft_minishell.h"

int open_file(char *filename, int red_type, t_pipes *pipes)
{
	int fd;

	fd = -1;
	if (red_type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0774);
	else if (red_type == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0774);
	if (fd != -1 && pipes->fd_out != STD_OUT)
		close (pipes->fd_out);
	if (red_type == 3)
	{
		fd = open(filename, O_RDONLY, 0644);
		if (fd != -1 && pipes->fd_in != STD_IN)
			close (pipes->fd_in);
	}
	return (fd); // if -1 - send error
}

char **dup_array(char **parso_args)
{
	int i;
	char **temp;

	temp = malloc(sizeof(char *) * size_arr(parso_args));
	i = 0;
	if (parso_args)
		if (parso_args[i])
			while (parso_args[i + 1])
			{
				temp[i] = ft_strdup(parso_args[i + 1]);
				i++;
			}
	temp[i] = NULL;
	return (temp);
}

char **update_array(char **all_args, t_pipes *pipes, t_parsing *parso)
{
	char	**temp;
	char	**temp2;
	char	*filename;
	int		fd;
	int 	fd2;

	fd = pipes->fd_out;
	fd2 = pipes->fd_in;
	filename = NULL;
	if (parso->redirects)
		if (parso->next->args)
			filename = parso->next->args[0];
	// IF FILENAME = NULL GENERATE ERROR

	temp = all_args;
	if (parso->redirects)
	{
		if (!ft_strncmp(parso->redirects, ">", 2))
			fd =  open_file(filename, 1, pipes);
		else if (!ft_strncmp(parso->redirects, ">>" ,3))
			fd = open_file(filename, 2, pipes);
		else if (!ft_strncmp(parso->redirects, "<" ,2))
			fd2 = open_file(filename, 3, pipes);
		if (fd2 != -1 && fd != -1)
		{
			temp2 = parso->next->args;
			//printf("next arr is %s an %s",parso->next->args[0], parso->next->args[1]);
			parso->next->args = dup_array(parso->next->args);
			clean_array(temp2);
		}
	}
	// update array
	temp = add_array_array(all_args, parso->args);

	// check fd for ERROR
	if (fd == -1 || fd2 == -1)
	{
		filename = ft_strjoin("minishell: ", filename);
		non_exit_failure(filename);
		free(filename);
		clean_array(temp);
		clean_array(all_args);
		return(NULL);
	}
	pipes->fd_in = fd2;
	pipes->fd_out = fd;
	clean_array(all_args);
	return (temp);
}

void print_array(char **args)
{
	int i;
	i = -1;
	//temp func
	printf("\nFINAL ARR HERE\n");
	if (args)
		while (args[++i])
			printf("%s\n",args[i]);
}

void last_command_exit(t_pipes *pipes)
{
	if (!g_exitcode)
	{
		waitpid(pipes->pid, pipes->stat_loc, 0);
		if (WIFEXITED(pipes->stat_loc))
			g_exitcode = WEXITSTATUS(pipes->stat_loc);
		if (!g_exitcode && WIFSIGNALED(pipes->stat_loc))
		{
			if (*pipes->stat_loc == 2 || *pipes->stat_loc == 3)
				ft_putendl_fd("", 2);
			g_exitcode= 128 + WTERMSIG(pipes->stat_loc);
		}
	}
}


int	make_redirects(t_pipes *pipes)
{

	char		**all_args;
	t_parsing	*begin;
	pid_t		pid;

	begin = pipes->parso;
	all_args = NULL;
 	//while (ft_strncmp(parso->redirects,">",1) ||	ft_strncmp(parso->redirects,">>",2))
	while (begin)
	{
		all_args = update_array(all_args, pipes, begin);
		begin = begin->next;
		if (!all_args)
			break ;
	}
	//printf("here am i");
	//print_array(all_args);
	// print all all_args
	// check file-descriptors and fork if_NOT_fork if desc else than std_in _ out  -> here we fork in case of NO PIPES
	//printf("out is %d",pipes->fd_out);
	pid = 0;
	//printf("out is %d\n",pipes->fd_out);
	if ((pipes->fd_in != STD_IN || pipes->fd_out != STD_OUT) && !g_exitcode)
		pid = fork();
	printf("in is %d and out is %d adn g_code %d\n",pipes->fd_in, pipes->fd_out,g_exitcode);
	if (!pid && !g_exitcode)
	{
		dup2(pipes->fd_in, STD_IN);
		dup2(pipes->fd_out, STD_OUT);
		if (pipes->next)
			close(pipes->next->fd_in);
		run_commands(all_args, pipes);
		if (pipes->fd_in != STD_IN || pipes->fd_out != STD_OUT)
		{
			// catch signal here;
			//if (!pipes->next)
			//last_command_exit(pipes);
			//printf("exit code is %d\n",g_exitcode);
			exit(g_exitcode);
		}
	}
	if (pipes->fd_in != STD_IN)
		close (pipes->fd_in);
	if (pipes->fd_out != STD_OUT)
		close (pipes->fd_out);
	// on error pid error - went away
	if (pipes->pid < 0)
		non_exit_failure("minishell: fork: ");
	clean_array(all_args);
	return (0);
}
