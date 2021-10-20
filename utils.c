/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:25:45 by lelle             #+#    #+#             */
/*   Updated: 2021/10/12 14:25:50 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_name(char *key_value)
{
	int	i;

	i = 0;
	if (ft_isalpha(key_value[0]) == 0 && key_value[0] != '_')
	{
		printf("export: `%s\': not a valid identifier\n", key_value);
		g_exitcode = 1;
		return (1);
	}
	while (key_value[++i] != '=' && key_value[i] != '\0')
	{
		if ((!ft_isalpha(key_value[i]) && !ft_isdigit(key_value[i]) && \
		key_value[i] != '_' && key_value[i] != '+') || (key_value[i] == '+' && key_value[i + 1] != '='))
		{
			printf("export: `%s': not a valid identifier\n", key_value);
			g_exitcode = 1;
			return (1);
		}

	}
	return (0);
}

int	len_key(char *str)
{
	char		*char_str;

	char_str = ft_strchr(str, '=');
	if (char_str != NULL)
		return (char_str - str + 1);
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
