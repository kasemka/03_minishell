/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:23:23 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 16:18:29 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	bultin(t_env *env, char **commands)
{
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
		return (0);
	return (1);
}

void	run_commands(char **commands, t_pipes *pipes)
{
	t_env	*env;

	env = pipes->env;
	if (!bultin(env, commands))
	{
		if (pipes->fd_in == STD_IN && pipes->fd_out == STD_OUT)
		{
			pipes->pid = fork();
			if (!pipes->pid)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				g_exitcode = other_cmd(env, commands);
				if (g_exitcode)
					exit(g_exitcode);
			}
			signal(SIGINT, SIG_IGN);
		}
		else
		{
			signal(SIGQUIT, SIG_DFL);
			g_exitcode = other_cmd(env, commands);
		}
	}
}
