/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:27:12 by lelle             #+#    #+#             */
/*   Updated: 2021/10/23 16:54:05 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	clean_print_status(t_env *lst)
{
	while (lst)
	{
		if (ft_strncmp(lst->key_vl, "_=", 2) != 0)
			lst->printed = -1;
		lst = lst->next;
	}
}

void	print_export2(t_env *min_l)
{
	if (ft_strchr(min_l->key_vl, '=') == 0)
		printf("declare -x %s\n", min_l->key_vl);
	else
	{
		printf("declare -x %.*s\"", len_key(min_l->key_vl) + 1, min_l->key_vl);
		printf("%s\"\n", len_key(min_l->key_vl) + 1 + min_l->key_vl);
	}
}

void	print_export(t_env *env)
{
	int		i;
	int		len;
	t_env	*t;
	t_env	*min_l;

	i = -1;
	len = len_lst(env);
	while (++i < len - 1)
	{
		t = env;
		while (t->printed >= 0 && t->next != NULL)
			t = t->next;
		min_l = t;
		while (t)
		{
			if (ft_strncmp(min_l->key_vl, t->key_vl, \
			ft_strlen(min_l->key_vl)) > 0 && t->printed == -1)
				min_l = t;
			t = t->next;
		}
		if (min_l->flg == 1 || min_l->flg == 2)
			print_export2(min_l);
		min_l->printed = 1;
	}
	clean_print_status(env);
}

//flag 1 = env, 2 = export, 3 = set, 4 = additional for HOME
void	print_env(t_env *lst, char *args)
{
	int		cmd_flag;

	cmd_flag = 0;
	if (ft_strncmp(args, "env", 4) == 0)
		cmd_flag = 1;
	else if (ft_strncmp(args, "export", 7) == 0)
		cmd_flag = 2;
	else if (ft_strncmp(args, "set_local", 10) == 0)
		cmd_flag = 3;
	if (cmd_flag != 2)
	{
		while (lst)
		{
			if (cmd_flag == 1 && lst->flg == 1)
				printf("%s \n", lst->key_vl);
			else if (cmd_flag == 3 && (lst->flg == 1 || lst->flg == 3))
				printf("%s \n", lst->key_vl);
			lst = lst->next;
		}
	}
	if (cmd_flag == 2)
		print_export(lst);
}
