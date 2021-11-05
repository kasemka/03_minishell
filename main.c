/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:48:45 by lelle             #+#    #+#             */
/*   Updated: 2021/11/05 12:48:48 by lelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*string;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = arr_to_list(envp, len_arr(envp));
	change_shlvl(env);
	add_addit_keys(env);
	rl_catch_signals = 0;
	g_exitcode = 0;
	while (1)
	{
		signal(SIGINT, sig_ignore);
		signal(SIGQUIT, SIG_IGN);
		string = readline(SHL_NAME);
		if (string == NULL)
			cntr_d();
		signal(SIGINT, cancel_cmd);
		add_history(string);
		parser(string, env);
		free(string);
	}
	free_list_env(env);
	return (g_exitcode);
}
