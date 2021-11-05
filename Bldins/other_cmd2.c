/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:26:57 by lelle             #+#    #+#             */
/*   Updated: 2021/11/05 11:22:04 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*ft_strdupc(char *s1, char c)
{
	int		i;
	char	*s2;
	int		len;

	i = 0;
	len = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[len] != c && s1[len] != '\0')
		len++;
	s2 = (char *)malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

// S_IXUSR execute/search permission, owner
char	*exec_curdir(char *cmd, char **commands, char **env_arr)
{
	struct stat	buf;
	char		*path;
	char		*cur_dir;

	cur_dir = malloc(4096 * sizeof(char));
	if (cur_dir == NULL)
		msg_mallocfail();
	getcwd(cur_dir, 4096);
	path = ft_strjoin(cur_dir, cmd);
	if (path == NULL)
		msg_mallocfail();
	execve(path, commands, env_arr);
	if (stat(path, &buf) == 0)
	{
		if (buf.st_mode & S_IXUSR)
			exit (0);
	}
	free(path);
	return (NULL);
}

char	*exec_cmd(char *key, char **commands, char **env_arr)
{
	char		*path;
	char		*cmd;
	char		*new_str;
	struct stat	buf;

	cmd = ft_strjoin("/", commands[0]);
	new_str = ft_strdupc(key, ':');
	if (new_str == NULL || cmd == NULL)
		return (msg_mallocfail_null());
	path = ft_strjoin(new_str, cmd);
	if (path == NULL)
		return (msg_mallocfail_null());
	execve(path, commands, env_arr);
	if (stat(path, &buf) == 0)
	{
		if (buf.st_mode & S_IXUSR)
			exit (0);
	}
	key = key + ft_strlen(new_str);
	if (*key == ':' && *(key + 1) != '\0')
		key++ ;
	free (new_str);
	free (path);
	return (key);
}

char	*path_err(char *cmd_input)
{
	msg_minsh_str(cmd_input, "No such file or directory");
	errno = 2;
	return ("unset");
}

//check if curr dir in PATH ::, :, :.:, .:, :. 
char	*find_path(t_env *env, char **commands, char **env_arr)
{
	char		*key;
	char		*cmd;

	key = NULL;
	cmd = ft_strjoin("/", commands[0]);
	if (cmd == NULL)
		return (NULL);
	if (find_by_key(env, "PATH") != NULL)
		key = (find_by_key(env, "PATH"))->key_vl + 5;
	if (!find_by_key(env, "PATH") || !key)
		return (path_err(commands[0]));
	while (*key)
	{
		if (*key == ':' || ft_strnstr(key, ".:", 2) || ft_strnstr(key, ".", 2))
		{
			exec_curdir(cmd, commands, env_arr);
			if (*key == '.')
				key++;
			while (*key == ':')
				key++ ;
		}
		else if (*key)
			key = exec_cmd(key, commands, env_arr);
	}
	return (NULL);
}
