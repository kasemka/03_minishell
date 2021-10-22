#include "ft_minishell.h"

char *get_dollar(int *i, char *str, char *out)
{
	char *var_val;
	char *temp1;

	temp1 = out;
	var_val = get_var(str, i);
	if (var_val)
	{
		out = ft_strjoin(temp1, var_val);
		free(temp1);
	}
	return (out); // should add free VAR_VAL later
}

void print_list(t_pipes *pipes)
{
	int i;

	while (pipes)
	{
		while (pipes->parso)
		{
			i = -1;
			if (pipes->parso->args)
				while (pipes->parso->args[++i])
					printf("<%s>",pipes->parso->args[i]);
			printf("\nredirect type %s\n", pipes->parso->redirects);
			pipes->parso = pipes->parso->next;
		}
		pipes = pipes->next;
	}
}

void free_list(t_parsing *parso)
{
	int i;

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

void free_pipes(t_pipes *pipes)
{
	t_pipes *begin;

	while (pipes)
	{
		begin = pipes;
		free_list(pipes->parso);
		pipes = pipes->next;
		free(begin);
	}
}

char *exit_failure(t_pipes *pipes, char *out)
{
	free(out);
	t_pipes *begin;
	while (pipes)
	{
		begin = pipes;
		free_list(pipes->parso);
		pipes = pipes->next;
		free(begin);
	}
	printf("%s\n",strerror(errno));
	return (NULL);
}

char *exit_failure_parso(t_parsing *parso)//, char *out)
{
//	free(out);
	free_list(parso);
	printf("%s\n",strerror(errno));
	return (NULL);
}
