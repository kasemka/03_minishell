/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:13:17 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/03 23:38:06 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void init_i_start_words(int *s_w_i)
{
	s_w_i[1] = 0;
	s_w_i[2] = -1;
}

/*void parse_pipe_inside(char *str,int i)
{
	if
}*/

int check_limit_vals(char *str, int j)
{
	int i;

	char c;

	c = str[j];
	i = 0;
	if (c != '\'' && c != '\"' && c != ' ' && c != '\0' \
		&& c != '>' && c != '<' && c != '|')
		i = 1;
	if ((c == '$' && ft_isalnum(str[j + 1])) || \
	(c == '$' && str[j + 1] == '?'))
		i = 0;
	return (i);
}

int if_pipe_or_redirect(char c)
{
	int i;

	i = 0;
	if (c == '>' || c == '<' || c == '|')
		i = 1;
	return (i);

}

char *parsing_cycle(t_pipes *pipes, char *str, char *out)
{
	int s_w_i[3];

	init_i_start_words(s_w_i);
	while (str[++s_w_i[2]])
	{
		ft_isspace(str, s_w_i);
		s_w_i[0] = s_w_i[2];
		if (s_w_i[2] == 0 && check_token_errors(str))
			return (NULL);
		while(check_limit_vals(str, s_w_i[2]))
			s_w_i[2]++;
		if (s_w_i[0] != s_w_i[2])
			parser_get_word(&out, str, s_w_i[0], &s_w_i[2]);
		if (str[s_w_i[2]] ==  '\'' || str[s_w_i[2]] ==  '\"')
			parser_get_slash(&out, str, &s_w_i[2], pipes);
		if (str[s_w_i[2]] == '$' && (ft_isalnum(str[s_w_i[2] + 1]) \
		|| str[s_w_i[2] + 1] == '?'))
			parser_get_dollar(&out, &s_w_i[2], str, pipes);
		//else if (str[s_w_i[2]] == '$')
		//	parser_get_dollar_alone(&out);
		if (str[s_w_i[2]] == ' ' || str[s_w_i[2]] == '\0' || \
			if_pipe_or_redirect(str[s_w_i[2]]))
			parser_get_zero_o_space(&out, &pipes, s_w_i, str);
		if (!out || str[s_w_i[2]] == '\0')
			break ;
	}
	return (out);
}

t_pipes *new_pipes(t_env *env)
{
	t_pipes		*new_pipe;
	t_parsing	*new_parso;

	new_pipe = malloc(sizeof(t_pipes));
	new_parso = new_list();
	new_pipe->parso = new_parso;
	new_pipe->next = NULL;
	new_pipe->fd_in = STD_IN;
	new_pipe->fd_out = STD_OUT;
	new_pipe->env = env;
	new_pipe->g_exit = g_exitcode;
	return (new_pipe);
}

char *parser(char *str, t_env *env)
{
	char *out;
//	t_parsing *parso;

	//parso = new_list();
	t_pipes *pipes;
	pipes = new_pipes(env);
	if (!pipes)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (exit_failure(pipes, NULL));
	if (*str == '\0')
		return ("");
	out = parsing_cycle(pipes, str, out);
	if (!out)
		return (exit_failure(pipes, out));
	g_exitcode = 0; // may be is should be somewhere else
	make_pipes(pipes);
	free (out);
	free_pipes(pipes);
	return (str);
}

// make funck here to read from terminal

// make func to send parso after reading str for next procedures

// do tasks with redirects
	// check if it is available
	// create file acc to it's type
	// update arguments array with args following after filenames
	// exit on strerror'
	// execute initial program with arguments available



void	change_shlvl(t_env * env)
{
	int		level;
	char	*lev_char;

	level = 0;
	env = find_by_key(env, "SHLVL");
	if (env)
	{
		if (ft_strncmp(env->key_vl, "SHLVL=", 7) != 0)
			level = ft_atoi(env->key_vl + 6);
		free(env->key_vl);
		if (level < 999)
		{
			level++;
			lev_char = ft_itoa(level);
			if (lev_char == NULL)
				exit (msg_mallocfail());
			env->key_vl = ft_strjoin("SHLVL=", lev_char);
			free(lev_char);
		}
		else
			env->key_vl = ft_strdup("SHLVL=");
		if (env->key_vl == NULL)
			exit (msg_mallocfail());
	}
}

//sigquit - ctrl + \
//sigint - ctrl + c
//str NULL - ctrl + D



int main(int argc, char **argv, char **envp)
{
	char *string;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = arr_to_list(envp, len_arr(envp));
	change_shlvl(env);
	add_addit_keys(env);
	rl_catch_signals = 0;
	g_exitcode = 0;
	//rl_outstream = stderr;
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
	//while(1);
	return (g_exitcode);
}
