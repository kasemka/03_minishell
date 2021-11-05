/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:26:57 by lelle             #+#    #+#             */
/*   Updated: 2021/11/05 11:22:04 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	other_cmd(t_env *env, char **commands)
{
	char		*path;
	char		**env_arr;

	env_arr = list_to_arr(env);
	if (env_arr == NULL)
		return (msg_mallocfail());
	if (commands[0][0] == '/' || commands[0][0] == '.' || \
	commands[0][0] == '~' || ft_strchr(commands[0], '/'))
	{
		path = commands[0];
		execve(path, commands, env_arr);
		msg_minsh_str(commands[0], strerror(errno));
	}
	else
		path = find_path(env, commands, env_arr);
	if (path == NULL)
		msg_minsh_str(commands[0], ": command not found");
	if (errno == 2)
		return (127);
	if (errno == 13)
		return (126);
	clean_array(env_arr);
	return (0);
}
