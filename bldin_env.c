#include "minishell.h"

//if PATH is removed, should not work
int	bldin_env(t_env *env)
{
	print_env(env, "env");
	return (0);
}
