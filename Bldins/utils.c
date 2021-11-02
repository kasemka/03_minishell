/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:45 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:58:49 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	check_name(char *key_value)
{
	int	i;

	i = 0;
	if (ft_isalpha(key_value[0]) == 0 && key_value[0] != '_')
		return(msg_error_export(key_value));
	while (key_value[++i] != '=' && key_value[i] != '\0')
	{
		if ((!ft_isalpha(key_value[i]) && !ft_isdigit(key_value[i]) && \
		key_value[i] != '_'))
		{
			if (key_value[i] == '+' && key_value[i + 1] == '=')
				return (0);
			return(msg_error_export(key_value));
		}
	}
	return (0);
}

int	len_key(char *str)
{
	char		*str_p;

	str_p = str;
	while (*str_p != '=' && *str_p != '+' && *str_p)
		str_p++;
	if (*str_p == '+' && *(str_p + 1) == '=')
		return (str_p - str);
	if (*str_p == '=')
		return (str_p - str);
	return (0);
}

t_env	*find_by_key(t_env *env, char *key_env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key_vl, key_env, ft_strlen(key_env)) == 0 && \
		env->key_vl[ft_strlen(key_env)] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	check_dir(char *home_dir)
{
	struct stat		buf;

	if (stat(home_dir, &buf))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(home_dir, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}
