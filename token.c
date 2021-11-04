/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:08:30 by lelle             #+#    #+#             */
/*   Updated: 2021/11/03 23:13:12 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
/*
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "Libft/libft.h"
*/

#define token  "minishell: syntax error near unexpected token `"

//int		g_exitcode;

//remove this func, it is already in minishell.h
int	len_arr_tkn(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

int print_token(char *sym)
{

	ft_putstr_fd(token, 2);
	ft_putstr_fd(sym, 2);
	ft_putstr_fd("\'\n", 2);
	return (258);
}


char *p_haystack(char *str, char **redir, int *len, int flag)
{
	int i;
	char *haystack;
	int	j;

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

int token_errors(char *str, char **redir, char **pipes_redir)
{
	char *haystack;
	char *haystack2;
	int	len;
	int len2;

	len = 0;
	len2 = 0;
	haystack2 = NULL;
	haystack = p_haystack(str, redir, &len, 1);
	if (haystack)
	{
		while (haystack[len] == ' ')
			len++;
		if (haystack[len] == '\0')
			return (print_token("newline"));
		haystack2 = p_haystack(haystack+len, pipes_redir, &len2, 2);
		if (haystack2)
		{
			haystack2[len2] = '\0';
			return (print_token(haystack2));
		}
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
		g_exitcode = print_token("||");
	else if (ft_strnstr(str, "|", 1))
		g_exitcode = print_token("|");
	else
		g_exitcode = token_errors(str, redir, pipes_redir);
	//clean_array(redir);
	//clean_array(pipes_redir);
	//printf("i'm our w g_exit = %d\n",g_exitcode);
	if (g_exitcode > 0)
		return (1);
	else
		return (0);
}



/*int main()
{
	char 	*str;
	g_exitcode = 0;


	while (1)
	{
		str = readline("minishell$ ");
		check_token_errors(str);
	}
	return (0);
}*/
