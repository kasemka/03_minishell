#include "minishell.h"

//$? - error num

int		bldin_echo(t_env **env_list, char **args)
{
	t_env	*env_temp;
	int		i;

	i = 0;
	env_temp = *env_list;
	while (args[++i] != NULL)
	{
		printf("%s ", args[i]);
	}
	printf("\n");
	return (0);
}