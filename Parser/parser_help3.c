#include "../ft_minishell.h"

int pipe_o_redirect(char *str)
{
	int len;

	if (*str != '\0')
	{
		len = ft_strlen(str);
		if (!ft_strncmp(str, "|", len) || !ft_strncmp(str, ">", len) || \
		!ft_strncmp(str, ">>", len)  || !ft_strncmp(str, "<", len)\
		|| !ft_strncmp(str, "<<", len))
			return (1);
	}
	return (0);
}

void ft_isspace(char *str, int *s_w_i)
{
	if (str[s_w_i[2]])
		while ((str[s_w_i[2]] ==' ' || str[s_w_i[2]] == '\t' || \
		str[s_w_i[2]] == '\n' || str[s_w_i[2]] == '\v' || str[s_w_i[2]] == '\f'\
		|| str[s_w_i[2]] == '\r') && str[s_w_i[2]])
			s_w_i[2]++;
}

char *get_var(char *str, int *i)
{
	char	*path;
	int		len;
	int		start_path;
	char	*glob_var;

	start_path = *i + 1;
	len = 0;
	while(ft_isalpha(str[++(*i)]))
		len++;
	if (len == 0 && str[*i] == '?')
	{
		glob_var = get_question();
		(*i)++;
	}
	else
	{
		path = ft_substr(str, start_path, len);
		glob_var = getenv(path);
		free(path);
	}
	return (glob_var);
}

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