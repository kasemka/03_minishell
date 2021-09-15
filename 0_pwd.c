#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>


int	msg_error()
{
	printf("%s\n", strerror(errno));
	return  (1);

}

int ft_pwd(void)
{
	char *pwd;
	char *buf;
	size_t size;

	size = 4096;
	buf = malloc(size * sizeof(char));
	if (buf == NULL)
		return (msg_error());
	pwd = getcwd(buf, size);
	if (pwd == NULL)
		return (msg_error());
	printf("%s\n", pwd);
	return (0);
}


int main(int argc, char **argv, char **env)
{
	int i;

	i = 0;
	(void)argc;
	(void)argv;
	(void)env;
//	while (env[i] != NULL)
//	{
//		printf("%s\n", env[i]);
//		i++;
//	}
	ft_pwd();
	return (0);
}
