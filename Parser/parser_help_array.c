#include "../ft_minishell.h"

void clean_array(char **args)
{
	int i;

	i = 0;
	if (args)
		while (args[i])
		{
			free(args[i]);
			i++;
		}
	free(args);
}
char **add_array_failure(char **temp)
{
	clean_array(temp);
	return (NULL);
}

char **add_array_element(t_parsing *parso, char *str, int words_num)
{
	char **temp;
	int i;

	i = 0;
	temp = malloc(sizeof(char *) * (words_num + 1));
	if (!temp)
		return (NULL);
	if (parso->args)
		while (parso->args[i])
		{
			temp[i] = ft_strdup(parso->args[i]);
			if (!temp[i])
				return (add_array_failure(temp));
		i++;
		}
	temp[i] = ft_strdup(str);
	if (!temp[i])
		return (add_array_failure(temp));
	i++;
	temp[i] = NULL;
	clean_array(parso->args);
	return (temp);
}

void parser_get_word(char **out, char *str, int start, int *i)
{
	char *temp;
	char *temp1;

	temp = *out;
	temp1 = ft_substr(str, start, *i - start);
	if (!temp1)
	{
		free (*out);
		*out = NULL;
		exit(EXIT_FAILURE);
	}
	*out = ft_strjoin(*out, temp1);
	if (!(*out))
		*out = NULL;
	free (temp1);
	free (temp);
}

int size_arr(char **arr)
{
	int i;

	i = 0;
	if (arr)
		while (arr[i])
			i++;
	return (i);
}

char **add_arr_to_arr(char **arr1, char **arr2, int start)
{
	int i;

	i = -1;
	if (arr2)
		while (arr2[++i])
		{
			arr1[start] = ft_strdup(arr2[i]);
			if (!arr1[start])
				return (add_array_failure(arr1));
			start++;
		}
	arr1[start] = NULL;
	return (arr1);
}

char **add_array_array(char **arr1, char **arr2)
{
	char **temp;
	int i;

	i = 0;
	temp = malloc(sizeof(char *) * (size_arr(arr1) + size_arr(arr2) + 1));
	if (!temp)
		return (NULL);
	temp = add_arr_to_arr(temp, arr1, 0);
	if (temp)
		temp = add_arr_to_arr(temp, arr2, size_arr(arr1));
	if (!temp)
		return (NULL);
	return (temp);
}
