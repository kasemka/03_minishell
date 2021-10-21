/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:20:50 by lelle             #+#    #+#             */
/*   Updated: 2021/10/12 14:24:52 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*define_home(t_env *env, int *flag, int *home_empty)
{
	char	*home;

	while (env != NULL)
	{
		if (ft_strncmp(env->key_vl, "HOME=", 5) == 0 && *flag == 4)
		{
			if (env->key_vl[5] != '\0')
			{
				home = env->key_vl + 5;
				*flag = env->flg;
				if (*flag != 4 || *home_empty == 1)
					break ;
			}
			if (env->key_vl[5] == '\0')
				*home_empty = 1;
		}
		env = env->next;
	}
	return (home);
}

int	change_dir(char **arg, char *home_dir)
{
	char	*home;
	int		status;

	status = 0;
	if (arg[1] == NULL || ft_strncmp(arg[1], "~", 2) == 0)
		chdir(home_dir);
	else if (arg[1][0] == '~')
	{
		home = ft_strjoin(home_dir, &arg[1][1]);
		if (home == NULL)
			return (msg_mallocfail());
		status = chdir(home);
	}
	else
		status = chdir(arg[1]);
	if (status != 0)
	{
		printf("cd: ");
		msg_error_str(arg[1]);
		return (1);
	}
	return (0);
}

int	change_oldpwd(t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp1 = find_by_key(env, "PWD");
	tmp2 = find_by_key(env, "OLDPWD");
	if (tmp2 != NULL)
		free (tmp2->key_vl);
	if (tmp1 == NULL && tmp2 == NULL)
	{
		add_new_list(env, 1, -1);
		last_list(env)->key_vl = ft_strdup("OLDPWD=");
		if (!last_list(env)->key_vl)
			return (msg_mallocfail());
	}
	else if (tmp1 != NULL && tmp2 != NULL)
	{
		tmp2->key_vl = ft_strjoin("OLDPWD=", tmp1->key_vl + 4);
		if (tmp2->key_vl == NULL)
			return (msg_mallocfail());
	}
	return (0);
}

int	change_pwd(t_env *env, char *newpwd)
{
	t_env	*tmp;

	tmp = find_by_key(env, "PWD");
	if (tmp == NULL)
	{
		add_new_list(env, 3, -1);
		tmp = last_list(env);
	}
	else
		free(tmp->key_vl);
	tmp->key_vl = ft_strjoin("PWD=", newpwd);
	free(newpwd);
	if (tmp->key_vl == NULL)
		return (msg_mallocfail());
	return (0);
}

// flag 4 = if HOME not in env
// flag=4 for additional home
int	bldin_cd(t_env *env, char **arg)
{
	char		*home_dir;
	int			flag;
	int			home_empty;
	char		*oldpwd;

	g_exitcode = 0;
	oldpwd = malloc(4096 * sizeof(char));
	if (oldpwd == NULL)
		msg_mallocfail();
	flag = 4;
	home_empty = 0;
	home_dir = define_home(env, &flag, &home_empty);
	if ((arg[1] == NULL || ft_strncmp(arg[1], "~", 2) == 0) && home_empty)
		return (0);
	else if (arg[1] == NULL && flag == 4)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	if (change_dir(arg, home_dir) == 1)
		return (1);
	getcwd(oldpwd, 4096);
	if (change_oldpwd(env) || change_pwd(env, oldpwd))
		return (1);
	return (0);
}
