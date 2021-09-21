#include "minishell.h"

// unset asdf asdfsd HOME - only HOME removed from env
// unset $HOME - if key in env: unset: `/Users/lelle': not a valid identifier.
// unset $COLORFGBG - not a valid identifier
// unset asdf asf - if key not in env: nothing happens
// unset _= - does not work
// unset with asdfasdf= -with "=" not a valid identifier

//flag = 1 env
//flag = 2 export
//flag = 3 set

int main(int argc, char **argv, char **env)
{
	int i;
	t_env *env_list;
	char  **commands;

	printf("______________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	i = 0;
	if (argc == 1)
	{
		printf("not enough argv\n");
		pause ();
	}
	env_list = arr_to_list(env, len_arr(env));
	// printfList(env_list);
	// printf("------------------------------------------------------------------\n");
	commands = ft_split(argv[1], ' ');

	if (ft_strncmp(commands[0], "env", 4) == 0)
		bldin_env(env_list);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		bldin_unset(&env_list, commands);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		ft_pwd();
	// if (ft_strncmp(commands[0], "export", 7) == 0)
	// 	bldin_export(&env_list, commands);
	// printf("------------------------------------------------------------------\n");
	// printfList(env_list);
	return (0);
}
