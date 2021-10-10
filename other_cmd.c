#include "minishell.h"

//check if curr dir in PATH ::, : at the beginnig
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

char	*search_in_curdir(char *cmd)
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
	if (stat(path, &buf) == 0)
		return (path);
	return (NULL);
}

char	*find_path(t_env *env, char *cmd_input)
{
	int			i;
	char		**envpath;
	char		*key;
	char		*cmd;
	char		*path;
	struct stat	buf;

	i = -1;
	if (stat(cmd_input, &buf) == 0)
		return (cmd_input);
	key = (find_by_key(env, "PATH"))->key_vl + 5;
	if (key == NULL)
		return (NULL);
	cmd = ft_strjoin("/", cmd_input);
	if (cmd == NULL)
		msg_mallocfail();
	envpath = ft_split(key, ':');
	if (envpath == NULL)
		msg_mallocfail();
	path = search_in_env(envpath, cmd);
	if (path == NULL && (ft_strnstr(key, "::", ft_strlen(key)) != NULL \
	|| key[0] == ':'))
		path = search_in_curdir(cmd);
	if (path != NULL)
		return (path);
	else
		free (path);
	return (NULL);
}

// bin/ls
//
int	other_cmd(t_env *env, char **commands)
{
	char	*path;
	char	**env_arr;

	if (env == NULL)
	{
		printf("%s: command not found\n", commands[0]);
		return (127);
	}
	env_arr = list_to_arr(env);
	if (env_arr == NULL)
		return (msg_mallocfail());
	path = find_path(env, commands[0]);
	if (path == NULL && ft_strchr(commands[0], '/') == 0)
	{
		printf("%s: command not found\n", commands[0]);
		return (127);
	}
	else if (path == NULL && ft_strchr(commands[0], '/') != 0)
	{
		printf("%s: No such file or directory\n", commands[0]);
		return (127);
	}
	if (execve(path, commands, env_arr) == -1)
		return (msg_error());
	ft_free_2array(env_arr);
	return (0);
}
