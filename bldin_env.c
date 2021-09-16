#include "minishell.h"

//env with no options or arguments
//env ba $s=s s=s
//env aaa=1 bbb=2 $c=c d
//env aaa=1 bbb=2 d $c=c
//env aaa=1 bbb=2 $HOME=c d
//env aaa=1 bbb=2 $v=c d
//env aaa=1 bbb=2 s $v=c d
//env s=s s=s!!!!!!!!!!!!!!!!!!!! отработать
//env c=c c=d !!!!!!!!!!!!!!!!!!!! отработать
//env =d


//find last change of key
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
			args[i][j] = '0';
			return (1);
		}
		j = 0;
	}
	return (0);
}

void	print_env(t_env *lst, char **args)
{
	while (lst)
	{
		if (lst->flag == 1)
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

	i = 0;
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
		print_env(env, args);
	print_args(args);
	return (0);
}
