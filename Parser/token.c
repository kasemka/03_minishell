/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:08:30 by lelle             #+#    #+#             */
/*   Updated: 2021/11/04 14:58:14 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	len_arr_tkn(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

char	*p_haystack(char *str, char **redir, int *len, int flag)
{
	int		i;
	char	*haystack;
	int		j;

	i = -1;
	j = len_arr_tkn(redir);
	haystack = NULL;
	while (++i < j)
	{
		if (flag == 1)
			haystack = ft_strnstr(str, redir[i], ft_strlen(str));
		else if (flag == 2)
			haystack = ft_strnstr(str, redir[i], ft_strlen(redir[i]));
		if (haystack)
		{
			*len = ft_strlen(redir[i]);
			return (haystack);
		}
	}
	return (NULL);
}

char	*skip_sym(char *haystack)
{
	if (ft_strnstr(haystack, "<<<", 3))
		haystack = haystack + 3;
	else if (ft_strnstr(haystack, "<<", 2))
	{
		haystack = haystack + 2;
		if (*haystack != '\0')
		{	
			if (*(haystack + 1) != '\0' && ft_strnstr(haystack, "||", 2))
				g_exitcode = print_token("||", 2);
			if (ft_strnstr(haystack, "|", 1))
				g_exitcode = print_token("|", 1);
			return ("stop");
		}
	}
	else if (ft_strnstr(haystack, "<>", 2) \
	|| ft_strnstr(haystack, ">>", 2) || ft_strnstr(haystack, ">|", 2))
		haystack = haystack + 2;
	else if (ft_strnstr(haystack, ">", 1) || ft_strnstr(haystack, "<", 1))
		haystack++;
	return (haystack);
}

int	token_errors(char *str, char **redir, char **pipes_redir)
{
	char	*haystack;
	char	*haystack2;
	int		len;
	int		len2;

	len = 0;
	len2 = 0;
	haystack2 = NULL;
	haystack = p_haystack(str, redir, &len, 1);
	while (haystack)
	{
		while (haystack[len] == ' ')
			len++;
		if (haystack[len] == '\0')
			return (print_token("newline", 7));
		haystack2 = p_haystack(haystack + len, pipes_redir, &len2, 2);
		if (haystack2 != NULL)
			return (print_token(haystack2, len2));
		haystack = skip_sym(haystack);
		if (ft_strnstr(haystack, "stop", 5))
			break ;
		if (haystack != NULL)
			haystack = p_haystack(haystack, redir, &len, 1);
	}
	return (0);
}

int	check_token_errors(char *str)
{
	char	**redir;
	char	**pipes_redir;

	redir = ft_split("<<< << <>  >> >| > < ", ' ');
	pipes_redir = ft_split("<<< << <>  >> >| > < || |", ' ');
	if (ft_strnstr(str, "||", 2))
		g_exitcode = print_token("||", 2);
	else if (ft_strnstr(str, "|", 1))
		g_exitcode = print_token("|", 1);
	else
		g_exitcode = token_errors(str, redir, pipes_redir);
	clean_array(redir);
	clean_array(pipes_redir);
	if (g_exitcode > 0)
		return (1);
	else
		return (0);
}
