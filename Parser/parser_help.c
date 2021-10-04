#include "../ft_minishell.h"

void parser_get_slash(char **out, char *str, int *i)
{
	*out =  get_quotes(i, str, *out); // continue checks here
	if (str[*i + 1] == ' ' || !str[*i + 1])
		(*i)++;
}

void parser_get_dollar(char **out, int *i, char *str)
{
	*out = get_dollar(i, str, *out);
	(*i)--;
	if (str[*i + 1] == ' ' || !str[*i + 1])
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

int parser_list_update(char **out, t_parsing **parso)
{
	int flag;

	flag = 0;
	(*parso)->red_o_pipe = ft_strdup(*out);
	if (!((*parso)->red_o_pipe))
		flag = 1;
	(*parso)->next = new_list();
	if (!((*parso)->next))
		flag = 1;
	if (!flag)
		(*parso) = (*parso)->next;

	return (flag);
}

void parser_get_zero_o_space(char **out, t_parsing **parso, int *words_num)
{
	int flag;

	flag = 0;
	if (pipe_o_redirect(*out)) // add str[i] == '|'
	{
		flag = parser_list_update(out, parso);
		*words_num = 0;
	}
	else
	{
		(*words_num)++;
		(*parso)->args = add_array_element((*parso), *out, *words_num);
		if (!(*parso)->args)
			flag = 1;
	}
	free(*out);
	if (flag)
		*out = NULL;
	if (*out)
		*out = ft_strdup("");
}
