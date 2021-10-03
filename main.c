#include "minishell.h"

//flag = 1 env
//flag = 2 export
//flag = 3 set

int main(int argc, char **argv, char **env)
{
	// int i;
	t_env *env_list;
	char  **commands;

	printf("______________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	// i = 0;
	if (argc == 1)
	{
		printf("not enough argv\n");
		pause ();
	}
	env_list = arr_to_list(env, len_arr(env));
	add_addit_home(env_list);
	// printfList(env_list);
	// printf("------------------------------------------------------------------\n");
	commands = ft_split(argv[1], ' ');

	if (ft_strncmp(commands[0], "env", 4) == 0)
		bldin_env(env_list);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		bldin_unset(&env_list, commands);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		bldin_pwd();
	if (ft_strncmp(commands[0], "export", 7) == 0 ||\
		ft_strncmp(commands[0], "set_local", 10) == 0)
		bldin_export(&env_list, commands);
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		bldin_echo(commands);
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		bldin_cd(env_list, commands);
	printf("______________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	// printf("\n\nENV\n");
	// print_env(env_list, "env");
	// printf("\n\nEXPORT\n");
	// print_env(env_list, "export");
	// printf("\n\nSET\n");
	// print_env(env_list, "set_local");
	return (0);
}
