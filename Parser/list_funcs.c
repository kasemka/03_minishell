/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:09:16 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 12:10:05 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

t_parsing	*new_list(void)
{
	t_parsing	*commons;

	commons = (t_parsing *)malloc(sizeof(t_parsing));
	if (!(commons))
		return (NULL);
	else
	{
		commons->args = NULL;
		commons->next = NULL;
		commons->redirects = NULL;
		commons->real_empty_str = 0;
		return (commons);
	}
}

t_parsing	*find_last(t_parsing *list)
{
	if (!list)
		return (list);
	while (list->next)
		list = list->next;
	return (list);
}

int	parser_list_update(char *out, t_pipes **pipes)
{
	int			flag;
	t_parsing	*last_parso;

	last_parso = find_last((*pipes)->parso);
	flag = 0;
	if (*out != '|')
	{
		last_parso->redirects = ft_strdup(out);
		last_parso->next = new_list();
		if (!((*pipes)->parso->redirects) || !(last_parso->next))
			flag = 1;
	}
	else
	{
		(*pipes)->next = new_pipes((*pipes)->env);
		(*pipes)->next->g_exit = (*pipes)->g_exit;
		if (!((*pipes)->next))
			flag = 1;
		else
			(*pipes) = (*pipes)->next;
	}
	return (flag);
}
