#include "minishell.h"

//flag = 1 env
//flag = 2 export
//flag = 3 set

int main(int argc, char **argv, char **envp)
{
	// int i;
	t_env	*env;
	char	**commands;

	(void)argc;
	(void)argv;

	if (argc == 1)
		return (0);
	// printf("1______________________________________________________________________________________________________________________________________________________________________________________________________________\n");
	// i = 0;
	env = arr_to_list(envp, len_arr(envp));
	add_addit_home(env);
	printf("2------------------------------------------------------------------\n");
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
		g_exitcode = bldin_cd(env, commands);
	else if (ft_strncmp(commands[0], "exit", 5) == 0)
		bldin_exit(commands);
	else
		g_exitcode = other_cmd(env, commands);
	free_list(env);
	printf("\nendddd...\n");
	return (g_exitcode);
}
