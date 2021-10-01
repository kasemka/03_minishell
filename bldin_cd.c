#include "minishell.h"

//export HOME=null; cd ~
int	bldin_cd(t_env *env_list, char **args)
{
	char	*home_dir;
	t_env	*tmp_list;
	int		i;

	i = 0;
	tmp_list = env_list;
	if (args[1][0] == '~')
	{
		while (tmp_list != NULL)
		{
			if (tmp_list)
		}
	}


	return (0);
}