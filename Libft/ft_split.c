/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:58:53 by gvolibea          #+#    #+#             */
/*   Updated: 2021/09/04 18:59:52 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_words(char const *s, char c)
{
	int		count;

	count = 0;
	if (ft_strlen(s) == 0)
		return (0);
	if (*s != c && *s)
		count = 1;
	while (*s)
	{
		if (*s == c && (*(s + 1) != c && *(s + 1) != '\0'))
			count++;
		s++;
	}
	return (count);
}

static void	free_array(char **out, int word)
{
	while (word)
	{
		free(out[word]);
		word--;
	}
	free(out);
}

static void	fill_array(char const *s, char c, char **out)
{
	int		pos;
	int		word;

	word = 0;
	while (*s)
	{
		pos = 0;
		while (*s == c)
			s++;
		if (!(*s))
			break ;
		while (s[pos] != c && s[pos] != '\0')
			pos++;
		out[word] = (char *)malloc(pos + 1);
		if (out[word] == NULL)
			free_array(out, word);
		ft_strlcpy(out[word], s, pos + 1);
		s = s + pos;
		word++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		words_count;
	char	**out;

	if (s == NULL)
		return (NULL);
	words_count = get_words(s, c);
	if (words_count == 0)
	{
		out = (char **)malloc(sizeof(NULL));
		if (out == NULL)
			return (NULL);
		out[0] = NULL;
		return (out);
	}
	out = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (out == NULL)
		return (NULL);
	fill_array(s, c, out);
	out[words_count] = NULL;
	return (out);
}
