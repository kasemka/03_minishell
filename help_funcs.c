#include "ft_minishell.h"

void print_list(t_parsing *parso)
{
	int i;

	while (parso)
	{
		i = -1;
		printf("here we are\n");
			printf("\nhere fin and str is %s\n",parso->args[0]);
		while (parso->args[++i])
			printf("<%s>",parso->args[i]);
		printf("\nredirect type %s\n", parso->red_o_pipe);
		parso = parso->next;
	}
}

void free_list(t_parsing *parso)
{
	int i;

	while (parso)
	{
		i = -1;
		while (parso->args[++i])
			free(parso->args[i]);
		free(parso->red_o_pipe);
		free(parso->args);
		free(parso);
		parso = parso->next;
	}
}

char *exit_failure(t_parsing *parso, char *out)
{
	free(out);
	free_list(parso);
	printf("%s\n",strerror(errno));
	return (NULL);
}
