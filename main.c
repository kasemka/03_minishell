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
	t_env env_list;
	char  **commands;

	i = 0;
	if (argc == 1)
	{
		printf("not enough argv\n");
		exit (1);
	}
	env_list = *arr_to_list(env, len_arr(env));
	printf("------------------------------------------------------------------\n");
	commands = ft_split(argv[1], ' ');
	// while (*commands!=NULL)
	// {
	// 	printf("%s\n", *commands);
	// 	commands++;
	// }
	while (*commands)
	{
		if (ft_strnstr(commands[0], "env", ft_strlen(commands[0])) != NULL)
		{
			bldin_env(commands, &env_list);
			break ;
		}
		commands++ ;
	}
	printf("------------------------------------------------------------------\n");
//	printfList(&env_list);
	return (0);
}
