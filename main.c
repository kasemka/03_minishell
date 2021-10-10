#include "minishell.h"

//flag = 1 env
//flag = 2 export
//flag = 3 set

int main(int argc, char **argv, char **envp)
{
	// int i;
	t_env *env;
	char  **commands;

	(void)argc;
	// printf("1______________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	// i = 0;
	env = arr_to_list(envp, len_arr(envp));
	add_addit_home(env);
	// printfList(env);
	// printf("2------------------------------------------------------------------\n");
	commands = ft_split(argv[1], ' ');
	if (ft_strncmp(commands[0], "env", 4) == 0)
		bldin_env(env);
	else if (ft_strncmp(commands[0], "unset", 6) == 0)
		bldin_unset(&env, commands);
	else if (ft_strncmp(commands[0], "pwd", 4) == 0)
		bldin_pwd();
	else if (ft_strncmp(commands[0], "export", 7) == 0 ||\
		ft_strncmp(commands[0], "set_local", 10) == 0)
		bldin_export(&env, commands);
	else if (ft_strncmp(commands[0], "echo", 5) == 0)
		bldin_echo(commands);
	else if (ft_strncmp(commands[0], "cd", 3) == 0)
		bldin_cd(env, commands);
	else if (ft_strncmp(commands[0], "exit", 5) == 0)
		bldin_exit(commands);
	else
		g_exitcode = other_cmd(env, commands);
	// printf("3______________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	// printf("\n\nENV\n");
	// print_env(env, "env");
	// printf("\n\nEXPORT\n");
	// print_env(env, "export");
	// printf("\n\nSET\n");
	// print_env(env, "set_local");
	// pause();
	return (0);
}
