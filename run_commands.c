#include "ft_minishell.h"

//flag = 1 env
//flag = 2 export
//flag = 4 additional home and pwd
void	run_commands(char **commands, t_pipes *pipes) //t_env *env)
{
	t_env	*env;
//	pid_t	pid;
//	int		status;

	env = pipes->env;
	if (ft_strncmp(commands[0], "env", 4) == 0)
		g_exitcode = bldin_env(env);
	else if (ft_strncmp(commands[0], "unset", 6) == 0)
		g_exitcode = bldin_unset(&env, commands);
	else if (ft_strncmp(commands[0], "pwd", 4) == 0)
		g_exitcode = bldin_pwd(env);
	else if (ft_strncmp(commands[0], "export", 7) == 0 || \
		ft_strncmp(commands[0], "set_local", 10) == 0)
		g_exitcode = bldin_export(&env, commands);
	else if (ft_strncmp(commands[0], "echo", 5) == 0)
		g_exitcode = bldin_echo(commands);
	else if (ft_strncmp(commands[0], "cd", 3) == 0)
		g_exitcode = bldin_cd(env, commands);
	else if (ft_strncmp(commands[0], "exit", 5) == 0)
		bldin_exit(commands);
	else
	{
		if (pipes->fd_in == STD_IN && pipes->fd_out == STD_OUT)
		{
			pipes->pid = fork();
			if (!pipes->pid)
			{
				// catch signal here
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				g_exitcode = other_cmd(env, commands);
			//	if (!pipes->next)
			//		if (!g_exitcode)
			//			last_command_exit(pipes);
				if (g_exitcode)
				{
					// send sig to parent
					exit(g_exitcode);
				}
			}
			signal(SIGINT, SIG_IGN);
//			waitpid(pid, &status, 0);
//			print_row(status);

		}
		else
		{
			signal(SIGQUIT, SIG_DFL);
			g_exitcode = other_cmd(env, commands);
		}
	}
}
