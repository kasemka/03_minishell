#include "minishell.h"

int	msg_error(void)
{
	printf("%s\n", strerror(errno));
	return (errno);
}

int	msg_mallocfail(void)
{
	printf("malloc fail\n");
	exit (1);
}

void	clean_print_status(t_env *lst)
{
	while (lst)
	{
		lst->printed = -1;
		lst = lst->next;
	}
}

//flag 1 = env, 2 = export, 3 = set 
void	print_export(t_env *lst)
{
	int		i;
	int		len;
	t_env	*tmp;
	t_env	*min_lst;

	i = 0;
	len = len_lst(lst);
	tmp = lst;
	while (i < len)
	{
		tmp = lst;
		while (tmp->printed >= 0 && tmp->next != NULL)
			tmp = tmp->next;
		min_lst = tmp;
		while (tmp)
		{
			if (ft_strncmp(min_lst->key_val, tmp->key_val, \
			ft_strlen(min_lst->key_val)) > 0 && tmp->printed == -1)
				min_lst = tmp;
			tmp = tmp->next;
		}
		if (min_lst->flag == 1 || min_lst->flag == 2)
			printf("declare -x %s\n", min_lst->key_val);
		min_lst->printed = 1;
		i++;
	}
	clean_print_status(lst);
}

//flag 1 = env, 2 = export, 3 = set, 4 = additional for HOME
void	print_env(t_env *lst, char *args)
{
	int		cmd_flag;

	cmd_flag = 0;
	if (ft_strncmp(args, "env", 4) == 0)
		cmd_flag = 1;
	else if (ft_strncmp(args, "export", 7) == 0)
		cmd_flag = 2;
	else if (ft_strncmp(args, "set_local", 10) == 0)
		cmd_flag = 3;
	if (cmd_flag != 2)
	{
		while (lst)
		{
			if (cmd_flag == 1 && lst->flag == 1)
				printf("%s \n", lst->key_val);
			else if (cmd_flag == 3 && (lst->flag == 1 || lst->flag == 3))
				printf("%s \n", lst->key_val);
			lst = lst->next;
		}
	}
	if (cmd_flag == 2)
		print_export(lst);
}
