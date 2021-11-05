/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:43:39 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/05 18:05:09 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	pipe_o_redirect(char *str)
{
	int	len;

	if (*str != '\0')
	{
		len = ft_strlen(str);
		if (!ft_strncmp(str, "|", len) || !ft_strncmp(str, ">", len) || \
		!ft_strncmp(str, ">>", len) || !ft_strncmp(str, "<", len) \
		|| !ft_strncmp(str, "<<", len))
			return (1);
	}
	return (0);
}

void	ft_isspace(char *str, int *s_w_i)
{
	if (str[s_w_i[2]])
		while ((str[s_w_i[2]] == ' ' || str[s_w_i[2]] == '\t' || \
		str[s_w_i[2]] == '\n' || str[s_w_i[2]] == '\v' || str[s_w_i[2]] == '\f'\
		|| str[s_w_i[2]] == '\r') && str[s_w_i[2]])
			s_w_i[2]++;
}

char	*get_val(char *str)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	while (str[i] != '=')
		i++;
	out = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!out)
		return (NULL);
	j = 0;
	while (str[++i])
	{
		out[j] = str[i];
		j++;
	}
	out[j] = '\0';
	return (out);
}

char	*ft_getenv(char *path, t_pipes *pipes)
{
	t_env	*temp;
	char	*temp_str;

	temp = pipes->env;
	while (temp)
	{
		if (ft_strncmp(temp->key_vl, path, ft_strlen(path)) == 0 && \
		temp->key_vl[ft_strlen(path)] == '=')
			return (get_val((temp->key_vl)));
		temp = temp->next;
	}
	temp_str = malloc(sizeof(char) * 1);
	temp_str = ft_strdup("");
	return (temp_str);
}

char	*get_var(char *str, int *i, t_pipes *pipes)
{
	char	*path;
	int		len;
	int		start_path;
	char	*glob_var;

	start_path = *i + 1;
	len = 0;
	while (ft_isalnum(str[++(*i)]))
		len++;
	if (len == 0 && str[*i] == '?')
	{
		glob_var = ft_itoa(pipes->g_exit);
		(*i)++;
	}
	else
	{
		path = ft_substr(str, start_path, len);
		glob_var = ft_getenv(path, pipes);
		free(path);
	}
	return (glob_var);
}
