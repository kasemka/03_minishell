#include "minishell.h"

//env with no options or arguments
//env ba $s=s s=s
//env aaa=1 bbb=2 $c=c d
//env aaa=1 bbb=2 d $c=c
//env aaa=1 bbb=2 $HOME=c d
//env aaa=1 bbb=2 $v=c d
//env aaa=1 bbb=2 s $v=c d
//env s=s s=s
//env c=c c=d
//env =d

void	word_to_space(char *word)
{
	while (*word != '\0')
	{
		*word = '_';
		word++ ;
	}
}

int	key_in_env(char *env, char **args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i] != NULL)
		i++;
	while (--i > 0)
	{
		while (env[j] != '=')
		{
			if (env[j] == args[i][j])
				j++;
			else
				break ;
		}
		if (env[j] == args[i][j])
		{
			printf("%s\n", args[i]);
			word_to_space(args[i]);
			return (1);
		}
		j = 0;
	}
	return (0);
}

void	print_env_flag(t_env *lst, char **args, int flag)
{
	while (lst)
	{
		if (lst->flag == flag)
		{
			if (len_arr(args) == 1 || !key_in_env(lst->key_value, args))
				printf("%s \n", lst->key_value);
		}
		lst = lst->next;
	}
}

void	print_args(char **args)
{
	int		i;
	int		len;
	int		len2;

	i = 0;
	len = len_arr(args) - 1;
	len2 = len - 1;
	while (len > 1)
	{
		while (len2 > 0)
		{
			if (ft_strnstr(args[len2], args[len], \
			index_strchr(args[len], '=') + 1))
				word_to_space(args[len2]);
			len2--;
		}
		len2 = len - 1;
		len--;
	}
	while (args[++i] != NULL)
	{
		if (ft_strchr(args[i], '=') != NULL)
			printf("%s\n", args[i]);
	}
}

int	bldin_env(char **args, t_env *env)
{
	int	ignore_env;
	int	i;

	i = 0;
	ignore_env = 0;
	while (args[++i] != NULL)
	{
		if (ft_strchr(args[i], '$') == NULL && ft_strchr(args[i], '=') == NULL)
		{
			printf("env: %s: No such file or directory\n", args[i]);
			return (1);
		}
		if (args[i][0] == '=')
		{
			printf("env: setenv %s: Invalid argument\n", args[i]);
			return (1);
		}
		if (args[i][0] == '-')
			ignore_env = 1;
	}
	if (ignore_env == 0)
		print_env_flag(env, args, 1);
	print_args(args);
	return (0);
}
