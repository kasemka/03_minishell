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

//check if curr dir in PATH ::, : at the beginnig

int	msg_minsh_str(char *cmd, char *err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (*err)
	{
		ft_putstr_fd(err, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (errno);
}

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

char	*search_in_env(char **envpath, char *cmd)
{
	char			*path;
	struct stat		buf;
	int				i;

	i = -1;
	while (envpath[++i] != NULL)
	{
		path = ft_strjoin(envpath[i], cmd);
		if (path == NULL)
			msg_mallocfail();
		if (stat(path, &buf) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

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
		if (buf.st_mode & S_IRUSR)
			exit (0);
	}
	free(path);
	return (NULL);
}

char *new_str_upd(char *key, char **commands, char **env_arr)
{
	char	*path;
	char	*cmd;
	char	*new_str;
	struct stat	buf;

	cmd = ft_strjoin("/", commands[0]);
	new_str = ft_strdupc(key, ':');
	if (new_str == NULL || cmd == NULL)
		return (NULL);
	path = ft_strjoin(new_str, cmd);
	if (path == NULL)
		return(NULL);
	execve(path, commands, env_arr);
	if (stat(path, &buf) == 0)
	{
		if (buf.st_mode & S_IRUSR)
			exit (0);
	}
	key = key + ft_strlen(new_str);
	if (*key == ':' && *(key + 1) != '\0')
		key++ ;
	free (new_str);
	free (path);
	return (key);
}

char *path_err(char *cmd_input)
{
	msg_minsh_str(cmd_input, "No such file or directory");
	errno = 2;
	return ("unset");
}


char	*find_path(t_env *env, char *cmd_input, char **commands, char **env_arr)
{
	char		*key;
	char		*cmd;
	//char		*path;
	//char		*new_str;
	//struct stat	buf;

	key = NULL;
	cmd = ft_strjoin("/", cmd_input);
	if (cmd == NULL)
		return (NULL);
	if (find_by_key(env, "PATH") != NULL)
		key = (find_by_key(env, "PATH"))->key_vl + 5;
	if (!find_by_key(env, "PATH") || !key)
		return (path_err(cmd_input));
	/*{
		msg_minsh_str(cmd_input, "No such file or directory");
		errno = 2;
		return ("unset");
	}*/
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
		{
		 	key = new_str_upd(key, commands, env_arr);
			/*new_str = ft_strdupc(key, ':');
			if (new_str == NULL)
				return (NULL);
			path = ft_strjoin(new_str, cmd);
			if (path == NULL)
				return(NULL);
			execve(path, commands, env_arr);
			if (stat(path, &buf) == 0)
			{
				if (buf.st_mode & S_IRUSR)
					exit (0);
			}
			key = key + ft_strlen(new_str);
			if (*key == ':' && *(key + 1) != '\0')
				key++ ;
			free (new_str);
			free (path);*/
		}
	}
	return (NULL);
}

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
		path = find_path(env, commands[0], commands, env_arr);
	if (path == NULL)
		msg_minsh_str(commands[0], ": command not found");
	if (errno == 2)
		return (127);
	if (errno == 13)
		return (126);
	clean_array(env_arr);
	return (0);
}
