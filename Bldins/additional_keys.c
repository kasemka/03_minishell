/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bldin_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:27:46 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:52:56 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

t_env	*find_by_key_flag(t_env *env, char *key_env, int flag)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key_vl, key_env, ft_strlen(key_env)) == 0 && \
		env->key_vl[ft_strlen(key_env)] == '=' && env->flg == flag)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	add_pwd(t_env *env)
{
	char	*pwd;
	t_env	*t;

	t = env;
	pwd = malloc(4096 * sizeof(char));
	if (pwd == NULL)
		return(msg_mallocfail());
	getcwd(pwd, 4096);
	while (t != NULL)
	{
		if (ft_strncmp(t->key_vl, "PWD=", 4) == 0 && t->flg == 4)
		{
			free(t->key_vl);
			break ;
		}
		t = t->next;
	}
	if (t == NULL)
	{
		add_new_list(env, 4, -1);
		t = last_list(env);
	}
	t->key_vl = ft_strjoin("PWD=", pwd);
	if (t->key_vl == NULL)
		return(msg_mallocfail());
	free(pwd);
	return (0);
}

//additionally HOME is added: if HOME is removed and cd ~ is executed
//flag = 4;
int	add_home(t_env *env)
{
	char	*home_addit;
	t_env	*tmp;

	tmp = find_by_key(env, "HOME");
	if (!tmp)
	{
		ft_putstr_fd("HOME should be in env as in real bash!\n", STDERR_FILENO);
		exit (1);
	}
	tmp = find_by_key_flag(env, "HOME", 4);
	home_addit = find_by_key_flag(env, "HOME", 1)->key_vl;
	if (tmp == NULL)
	{
		if (add_new_list(env, 4, -1))
			return (msg_mallocfail());
		(last_list(env))->key_vl = ft_strdup(home_addit);
		if ((last_list(env))->key_vl == NULL)
			return (msg_mallocfail());
	}
	return (0);
}

int	add_addit_keys(t_env *env)
{
	if (add_home(env) || add_pwd(env))
		return (g_exitcode);
	return(0);
}