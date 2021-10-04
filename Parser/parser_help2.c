#include "../ft_minishell.h"

char *update_path(char *path, char *str, int start, int len)
{
	char *temp;
	char *temp1;

	temp = path;
	temp1 = ft_substr(str, start, len);
	path = ft_strjoin(path, temp1);
	free(temp1);
	free(temp);
	return (path);
}

char *get_dollar(int *i, char *str, char *out)
{
	char *var_val;
	char *temp1;

	temp1 = out;
	var_val = get_var(str, i);
	if (var_val)
	{
		out = ft_strjoin(temp1, var_val);
		free(temp1);
	}
	return (out); // should add free VAR_VAL later
}

char *get_str_between(char *str, int *i, char c)
{
	char *out;
	int len;

	(*i)++;
	len = 0;
	while (str[(*i)++] != c)
		len++;
	out = ft_substr(str, *i - len - 1, len);
	(*i)--;
	return(out);
}

char *get_question(void)
{
	char *test;
	test = malloc(4);
	test = "123";
	return (test);
}

char *get_str_between_dbl(char *str, int *i, char c)
{
	int len;
	int start_path;
	char *path;

	(*i)++;
	len = 0;
	start_path = 0;
	path = ft_strdup("");
	while (str[(*i)] != c)
	{
		if (str[(*i)] == '$' && (ft_isalnum((str[(*i + 1)])) || \
		str[*i + 1] == '?'))
		{
			path = update_path(path, str, *i - len, len);
			path = get_dollar(i, str, path);
			len = 0;
			continue;
		}
		(*i)++;
		len++;
	}
	path = update_path(path, str, *i - len, len);
	return (path);
}

char *get_quotes(int *i, char *str, char *out)
{
	char *temp;
	char *temp1;

	temp1 = out;
	if (str[*i] == '\'')
		temp = get_str_between(str, i, str[*i]);
	else
		temp = get_str_between_dbl(str, i, str[*i]);
	out = ft_strjoin(temp1, temp);
	free (temp1);
	free (temp);
	return (out);
}
