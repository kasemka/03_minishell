#include "../ft_minishell.h"

int open_file(char *filename, int red_type)
{
	int fd;

	fd = -1;
	if (red_type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0774);
	else if (red_type == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0774);
	else
		fd = open(filename, O_RDONLY, 0644);

	// add closing
	return (fd); // if -1 - send error
}

char **dup_array(char **parso_args)
{
	int i;
	char **temp;

	temp = malloc(sizeof(char *) * size_arr(parso_args) + 1);
	i = 0;
	if (parso_args)
		while (parso_args[i])
		{
			temp[i] = ft_strdup(parso_args[i]);
			i++;
		}
	temp[i] = NULL;
	return (temp);
}

char **update_array(char **all_args, t_pipes *pipes, t_parsing *parso)
{
	char	**temp;
	char	*filename;

	filename = NULL;
	if (parso->redirects)
		if (parso->next->args)
			filename = parso->next->args[0];
	// IF FILENAME = NULL GENERATE ERROR
	temp = all_args;
	if (parso->redirects)
	{
		if (!ft_strncmp(parso->redirects, ">", 2))
			pipes->fd_out = open_file(filename, 1);
		else if (!ft_strncmp(parso->redirects, ">>" ,3))
			pipes->fd_out = open_file(filename, 2);
		else if (!ft_strncmp(parso->redirects, "<" ,2))
			pipes->fd_in = open_file(filename, 3);
	}
	// update array
	temp = add_array_array(all_args, parso->args);
	clean_array(all_args);
	// check fd for ERROR
	if (pipes->fd_in == -1 || pipes->fd_out == -1)
		exit_failure(pipes, NULL);
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
	}
	// print all all_args
	// check file-descriptors and fork if_NOT_fork if desc else than std_in _ out  -> here we fork in case of NO PIPES
	//printf("out is %d",pipes->fd_out);
	pid = 0;
	char a;
	a = 'a';
	if (pipes->fd_in != STD_IN || pipes->fd_out != STD_OUT)
		pid = fork();
	if (!pid)
	{
		dup2(pipes->fd_in, STD_IN);
		dup2(pipes->fd_out, STD_OUT);
		// close file_desc of in if pipes
		if (pipes->next)
			close(pipes->next->fd_in);
		write(1, &a, 1);
		//run_commands(all_args, pipes->env);
	}
	if (pipes->fd_in != STD_IN )
		close (pipes->fd_in);
	if (pipes->fd_out != STD_OUT)
		close (pipes->fd_out);
	//print_array(all_args);
	clean_array(all_args);
	return (0);
}
