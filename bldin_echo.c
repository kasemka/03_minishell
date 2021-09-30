#include "minishell.h"

//$? - error num

int		bldin_echo(t_env **env_list, char **args)
{
	t_env	*env_temp;
	int		i;

	i = 0;
	env_temp = *env_list;
	if (ft_strncmp(args[1], "-n", 3) == 0)
		i++;
	while (args[++i] != NULL)
	{
		printf("%s ", args[i]);
	}
	if (ft_strncmp(args[1], "-n", 3) != 0)
		printf("\n");
	return (0);
}