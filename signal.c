/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelle <lelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 23:39:25 by lelle             #+#    #+#             */
/*   Updated: 2021/10/30 13:34:50 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void sig_ignore(int signo)
{
	(void)signo;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	cancel_cmd(int signo)
{
	(void)signo;
	write(1, "\n", 1);
}

void quit_cmd(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit: 3\n", 1);
	// exit(0);
}