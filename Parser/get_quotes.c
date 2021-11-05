/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:43:33 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 20:50:38 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*update_path(char *path, char *str, int start, int len)
{
	char	*temp;
	char	*temp1;

	temp = path;
	temp1 = ft_substr(str, start, len);
	path = ft_strjoin(path, temp1);
	free(temp1);
	free(temp);
	if (!temp1 || !path)
		return (NULL);
	return (path);
}

char	*get_str_between(char *str, int *i, char c)
{
	char	*out;
	int		len;

	(*i)++;
	len = 0;
	while (str[(*i)++] != c)
		len++;
	out = ft_substr(str, *i - len - 1, len);
	(*i)--;
	return (out);
}

char	*get_str_between_dbl(char *str, int *i, char c, t_pipes *pipes)
{
	int		len;
	int		start_path;
	char	*path;

	(*i)++;
	len = 0;
	start_path = 0;
	path = ft_strdup("");
	while (str[(*i)] != c)
	{
		if (str[(*i)] == '$' && (ft_isalnum((str[(*i + 1)])) || \
		str[*i + 1] == '?'))
		{
			path = update_path(path, str, *i - len, len);
			path = get_dollar(i, str, path, pipes);
			len = 0;
			continue ;
		}
		(*i)++;
		len++;
	}
	path = update_path(path, str, *i - len, len);
	return (path);
}

char	*get_quotes(int *i, char *str, char *out, t_pipes *pipes)
{
	char	*temp;
	char	*temp1;

	temp1 = out;
	if (str[*i] == '\'')
		temp = get_str_between(str, i, str[*i]);
	else
		temp = get_str_between_dbl(str, i, str[*i], pipes);
	out = ft_strjoin(temp1, temp);
	free (temp1);
	free (temp);
	return (out);
}

void	parser_get_slash(char **out, char *str, int *i, t_pipes *pipes)
{
	*out = get_quotes(i, str, *out, pipes);
	if (!ft_strncmp(*out, "", 1))
		pipes->parso->real_empty_str = 1;
	if (str[*i + 1] == ' ' || !str[*i + 1])
		(*i)++;
}
