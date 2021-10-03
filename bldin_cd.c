#include "minishell.h"

char	*define_home(t_env *env, int *flag, int *home_empty)
{
	char	*home;

	while (env != NULL)
	{
		if (ft_strncmp(env->key_val, "HOME=", 5) == 0 && *flag == 4)
		{
			if (env->key_val[5] != '\0')
			{
				home = env->key_val + 5;
				*flag = env->flag;
				if (*flag != 4 || *home_empty == 1)
					break ;
			}
			if (env->key_val[5] == '\0')
				*home_empty = 1;
		}
		env = env->next;
	}
	return (home);
}

// int	change_dir(t_env *env, char **arg, char *home_dir)
int	change_dir(char **arg, char *home_dir)
{
	char	*home;
	int		dir_changed;

	dir_changed = 0;
	if (arg[1] == NULL || ft_strncmp(arg[1], "~", 2) == 0)
		dir_changed = chdir(home_dir);
	else if (arg[1][0] == '~')
	{
		home = ft_strjoin(home_dir, &arg[1][1]);
		if (home == NULL)
			return (msg_error());
		dir_changed = chdir(home);
	}
	else
		dir_changed = chdir(arg[1]);
	if (dir_changed == 1)
	{
		msg_error();
		return (msg_error());
	}
	return (0);
}

int	change_oldpwd(t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp1 = env;
	tmp2 = env;
	while (tmp1 != NULL)
	{
		if (ft_strncmp(tmp1->key_val, "PWD", 4) == 0)
			break ;
		tmp1 = tmp1->next;
	}
	while (tmp2 != NULL)
	{
		if (ft_strncmp(tmp2->key_val, "OLDPWD", 4) == 0)
		{
			free(tmp2->key_val);
			break ;
		}
		if (tmp2->next == NULL)
		{
			add_new_list(env, 3, -1);
			tmp2 = tmp2->next;
			break ;
		}
		tmp2 = tmp2->next;
	}
	if (tmp1 == NULL)
		tmp2->key_val = ft_strdup("OLDPWD=");
	else
		tmp2->key_val = ft_strdup(tmp1->key_val + 3);
	if (tmp2 == NULL)
		return (msg_error());
	return (0);
}

int	change_pwd(t_env *env, char *newpwd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->key_val, "PWD", 4) == 0)
		{
			free(tmp->key_val);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp->next == NULL && ft_strncmp(tmp->key_val, "PWD", 4) != 0)
	{
		add_new_list(env, 3, -1);
		tmp = tmp->next;
	}
	tmp->key_val = ft_strjoin("PWD=", newpwd);
	free(newpwd);
	if (tmp == NULL)
		return (1);
	return (0);
}

// flag 4 means that HOME was not found variables
// export HOME=null; cd ~ or cd - both do not work and show error
// export HOME=, cd ~ or cd - both do not work. no error
// HOME=solong, cd ~ or cd - both do not work
// unset HOME, cd ~ or cd - first do not work and show error
// flag=4 for additional home
int	bldin_cd(t_env *env, char **arg)
{
	char	*home_dir;
	int		flag;
	int		home_empty;
	char	*newpwd;

	newpwd = malloc(4096 * sizeof(char));
	if (newpwd == NULL)
		return (msg_error());
	flag = 4;
	home_empty = 0;
	home_dir = define_home(env, &flag, &home_empty);
	if ((arg[1] == NULL || ft_strncmp(arg[1], "~", 2) == 0) && home_empty)
		return (1);
	else if (arg[1] == NULL && flag == 4)
	{
		printf(" cd: HOME not set\n");
		return (1);
	}
	if (change_dir(arg, home_dir) == 1)
		return (1);
	getcwd(newpwd, 4096);
	if (change_oldpwd(env) || change_pwd(env, newpwd))
		return (msg_error());
	return (0);
}
