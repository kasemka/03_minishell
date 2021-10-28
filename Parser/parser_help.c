#include "../ft_minishell.h"

void parser_get_slash(char **out, char *str, int *i, t_parsing *parso)
{
	*out =  get_quotes(i, str, *out); // continue checks here
	if (!ft_strncmp(*out,"",1))
		parso->real_empty_str = 1;
	if (str[*i + 1] == ' ' || !str[*i + 1])
		(*i)++;
}

void parser_get_dollar(char **out, int *i, char *str)
{
	*out = get_dollar(i, str, *out);
	(*i)--;
	//printf("i'm at simb %c and out is %s\n",str[*i],*out);
	if (str[*i + 1] == ' ' || str[*i + 1] == '\0')
		(*i)++;
}

void parser_get_dollar_alone(char **out)
{
	char *temp1;
	char *temp;

	temp1 = "$";
	temp = *out;
	*out = ft_strjoin(*out, temp1);
	free (temp);
}

/*int parser_list_update(char *out, t_parsing **parso)
{
	int flag;

	flag = 0;
	(*parso)->redirects = ft_strdup(out);
	if (!((*parso)->redirects))
		flag = 1;
	(*parso)->next = new_list();
	if (!((*parso)->next))
		flag = 1;
	if (!flag)
		(*parso) = (*parso)->next;

	return (flag);
}*/

t_parsing	*find_last(t_parsing *list)
{
	if (!list)
		return (list);
	while (list->next)
		list = list->next;
	return (list);
}


int parser_list_update(char *out, t_pipes **pipes)
{
	int flag;
	t_parsing *last_parso;

	last_parso = find_last((*pipes)->parso);
	flag = 0;
	if (*out != '|')
	{
		last_parso->redirects = ft_strdup(out);
		last_parso->next  = new_list();
		//printf("in this list red %s is and 1st arg is %s",last_parso->redirects, last_parso->args[0]);
		if (!((*pipes)->parso->redirects) || !(last_parso->next))
			flag = 1;
	}
	else
	{
		//(*pipes)->pipe = 1;
		(*pipes)->next = new_pipes((*pipes)->env);
		if(!((*pipes)->next))
			flag = 1;
		else
			(*pipes) = (*pipes)->next;
	}
	return (flag);
}

char *get_pipe_o_redirect(char *str, int *s_w_i)
{
	if (str[s_w_i[2]] == '|')
		return ("|");
	if (str[s_w_i[2]] == '>')
	{
		if (str[s_w_i[2] + 1] == '>')
		{
			s_w_i[2]++;
			return (">>");
		}
		return (">");
	}
	if (str[s_w_i[2]] == '<')
	{
		if (str[s_w_i[2] + 1] == '<')
		{
			s_w_i[2]++;
			return ("<<");
		}
		return ("<");
	}
	return (NULL);
}

void parser_get_zero_o_space(char **out, t_pipes **pipes, int *s_w_i, \
	char *str)
{
	int flag;
	char *temp;
	t_parsing *last_parso;
	flag = 0;
	// if new word - add to

	if ((!pipe_o_redirect(*out) && ft_strncmp(*out, "", 1)) || \
 		(!ft_strncmp(*out, "", 1) && (*pipes)->parso->real_empty_str))
	{
		(s_w_i[1])++;
		last_parso = find_last((*pipes)->parso);
		//(*pipes)->parso
		last_parso->args = add_array_element(last_parso, *out, s_w_i[1]);
		if (!last_parso->args)
			flag = 1;
	}
	if (pipe_o_redirect(*out) || if_pipe_or_redirect(str[s_w_i[2]])) // add str[i] == '|'
	{
		temp = *out;
		if (if_pipe_or_redirect(str[s_w_i[2]]))
			temp = get_pipe_o_redirect(str, s_w_i);
		//flag = parser_list_update(temp, (*pipes)->parso);
		flag = parser_list_update(temp, pipes);
		s_w_i[1] = 0;
	}
	free(*out);
	(*pipes)->parso->real_empty_str = 0;
	if (flag)
		*out = NULL;
	if (*out)
		*out = ft_strdup("");
}
