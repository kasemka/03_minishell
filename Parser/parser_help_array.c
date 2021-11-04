/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:43:35 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 11:55:51 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	clean_array(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
	}
	free(args);
}

char	**add_array_element(t_parsing *parso, char *str, int words_num)
{
	char	**temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char *) * (words_num + 1));
	if (!temp)
		return (NULL);
	if (parso->args)
	{
		while (parso->args[i])
		{
			temp[i] = ft_strdup(parso->args[i]);
			if (!temp[i])
				must_exit_failure(NULL);
			i++;
		}
	}
	temp[i] = ft_strdup(str);
	if (!temp[i])
		must_exit_failure(NULL);
	i++;
	temp[i] = NULL;
	clean_array(parso->args);
	return (temp);
}

int	size_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
		while (arr[i])
			i++;
	return (i);
}

char	**add_arr_to_arr(char **arr1, char **arr2, int start)
{
	int	i;

	i = -1;
	if (arr2)
	{
		while (arr2[++i])
		{
			arr1[start] = ft_strdup(arr2[i]);
			if (!arr1[start])
				must_exit_failure(NULL);
			start++;
		}
	}
	arr1[start] = NULL;
	return (arr1);
}

char	**add_array_array(char **arr1, char **arr2)
{
	char	**temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char *) * (size_arr(arr1) + size_arr(arr2) + 1));
	if (!temp)
		return (NULL);
	temp = add_arr_to_arr(temp, arr1, 0);
	if (temp)
		temp = add_arr_to_arr(temp, arr2, size_arr(arr1));
	if (!temp)
		return (NULL);
	return (temp);
}
