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

void get_question(void)
{
	printf("%d\n",g_exitcode);
}

char *get_str_between_dbl(char *str, int *i, char c, t_pipes *pipes)
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
			path = get_dollar(i, str, path, pipes);
			len = 0;
			continue;
		}
		(*i)++;
		len++;
	}
	path = update_path(path, str, *i - len, len);
	return (path);
}

char *get_quotes(int *i, char *str, char *out, t_pipes *pipes)
{
	char *temp;
	char *temp1;

	temp1 = out;
	if (str[*i] == '\'')
		temp = get_str_between(str, i, str[*i]);
	else
		temp = get_str_between_dbl(str, i, str[*i], pipes);
	out = ft_strjoin(temp1, temp);
	free (temp1);
	free (temp);
	return (out);
}
