#include "minishell.h"

char	*define_home(t_env *env, int *flag, int *home_empty)
{
	char	*home;

	while (env != NULL)
	{
		if (ft_strncmp(env->key_val, "HOME=", 5) == 0 && flag == 4)
		{
			if (env->key_val[5] != '\0')
			{
				home = env->key_val + 5;
				*flag = env->flag;
				if (*flag != 4 || *home_empty)
					break ;
			}
			if (env->key_val[5] == '\0')
				*home_empty = 1;
			
		}
		env = env->next;
	}
	return (home);
}



// export HOME=null; cd ~ or cd - both do not work and show error
// export HOME=, cd ~ or cd - first do not work
// HOME=solong, cd ~ or cd - both do not work
// unset HOME, cd ~ or cd - first do not work and show error
int	bldin_cd(t_env *env, char **arg)
{
	char	*home_dir;
	int		len;
	int		flag;
	int		home_empty;

	flag = 4;
	home_empty = 0;
	len = ft_strlen(arg[1]);
	home_dir = define_home(env, &flag, &home_empty);

	


	return (0);
}