/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvolibea <gvolibea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:11:19 by gvolibea          #+#    #+#             */
/*   Updated: 2021/11/04 13:12:53 by gvolibea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	open_file(char *filename, int red_type, t_pipes *pipes)
{
	int	fd;

	fd = -1;
	if (red_type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0774);
	else if (red_type == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0774);
	if (fd != -1 && pipes->fd_out != STD_OUT)
		close (pipes->fd_out);
	if (red_type == 3)
	{
		fd = open(filename, O_RDONLY, 0644);
		if (fd != -1 && pipes->fd_in != STD_IN)
			close (pipes->fd_in);
	}
	return (fd);
}

char	**dup_array(char **parso_args)
{
	int		i;
	char	**temp;

	temp = malloc(sizeof(char *) * size_arr(parso_args));
	if (!temp)
		must_exit_failure(NULL);
	i = 0;
	if (parso_args)
	{
		if (parso_args[i])
		{
			while (parso_args[i + 1])
			{
				temp[i] = ft_strdup(parso_args[i + 1]);
				i++;
			}
		}
	}
	temp[i] = NULL;
	return (temp);
}

char	**fd_failure(char *filename, char **temp, char **all_args)
{
	filename = ft_strjoin("minishell: ", filename);
	non_exit_failure(filename);
	free(filename);
	clean_array(temp);
	clean_array(all_args);
	return (NULL);
}

char	*update_fds(int *fd, int *fd2, t_parsing *parso, t_pipes *pipes)
{
	char	*filename;
	char	**temp2;

	filename = NULL;
	if (parso->redirects)
		if (parso->next->args)
			filename = parso->next->args[0];
	if (parso->redirects)
	{
		if (!ft_strncmp(parso->redirects, ">", 2))
			*fd = open_file(filename, 1, pipes);
		else if (!ft_strncmp(parso->redirects, ">>", 3))
			*fd = open_file(filename, 2, pipes);
		else if (!ft_strncmp(parso->redirects, "<", 2))
			*fd2 = open_file(filename, 3, pipes);
		if (*fd2 != -1 && *fd != -1)
		{
			temp2 = parso->next->args;
			parso->next->args = dup_array(parso->next->args);
			clean_array(temp2);
		}
	}
	return (filename);
}

char	**update_array(char **all_args, t_pipes *pipes, t_parsing *parso)
{
	char	**temp;
	char	*filename;
	int		fd;
	int		fd2;

	fd = pipes->fd_out;
	fd2 = pipes->fd_in;
	temp = all_args;
	filename = update_fds(&fd, &fd2, parso, pipes);
	temp = add_array_array(all_args, parso->args);
	if (fd == -1 || fd2 == -1)
		return (fd_failure(filename, temp, all_args));
	pipes->fd_in = fd2;
	pipes->fd_out = fd;
	clean_array(all_args);
	return (temp);
}
