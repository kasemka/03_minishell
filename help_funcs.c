#include "ft_minishell.h"

void	parser_get_word(char **out, char *str, int start, int *i)
{
	char	*temp;
	char	*temp1;

	temp = *out;
	temp1 = ft_substr(str, start, *i - start);
	if (!temp1)
	{
		free (*out);
		*out = NULL;
		exit(EXIT_FAILURE);
	}
	*out = ft_strjoin(*out, temp1);
	if (!(*out))
		*out = NULL;
	free (temp1);
	free (temp);
}

void	free_list(t_parsing *parso)
{
	int	i;

	while (parso)
	{
		i = -1;
		if (parso->args)
			while (parso->args[++i])
				free(parso->args[i]);
		free(parso->redirects);
		free(parso->args);
		free(parso);
		parso = parso->next;
	}
}

void	free_pipes(t_pipes *pipes)
{
	t_pipes	*begin;

	while (pipes)
	{
		begin = pipes;
		free_list(pipes->parso);
		pipes = pipes->next;
		free(begin);
	}
}

t_pipes	*new_pipes(t_env *env)
{
	t_pipes		*new_pipe;
	t_parsing	*new_parso;

	new_pipe = malloc(sizeof(t_pipes));
	new_parso = new_list();
	if (!new_pipe || !new_parso)
		return (NULL);
	new_pipe->parso = new_parso;
	new_pipe->next = NULL;
	new_pipe->fd_in = STD_IN;
	new_pipe->fd_out = STD_OUT;
	new_pipe->env = env;
	new_pipe->g_exit = g_exitcode;
	return (new_pipe);
}
